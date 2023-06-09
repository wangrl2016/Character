//
// Created by wangrl2016 on 2023/6/29.
//

#include <glog/logging.h>

#include "media/filters/ffmpeg_video_encoder.h"

namespace media {
    constexpr int kStreamFrameRate = 25;
    constexpr int kStreamDuration = 10; // 10s
    constexpr AVPixelFormat kStreamPixelFormat = AV_PIX_FMT_YUV420P;

    FFmpegVideoEncoder::FFmpegVideoEncoder() {

    }

    FFmpegVideoEncoder::~FFmpegVideoEncoder() {

    }

    bool FFmpegVideoEncoder::Open(const std::string& file_path) {
        int ret;
        AVDictionary* opt = nullptr;

        // allocate the output media context
        avformat_alloc_output_context2(&output_format_context_,
                                       nullptr,
                                       nullptr,
                                       file_path.c_str());
        if (!output_format_context_) {
            LOG(ERROR) << "Could not deduce output format from file extension: using MPEG.";
            avformat_alloc_output_context2(&output_format_context_,
                                           nullptr,
                                           "mpeg",
                                           file_path.c_str());
        }
        if (!output_format_context_)
            return false;

        auto fmt = output_format_context_->oformat;

        // Add the audio and video streams using the default format codecs
        // and initialize the codecs.
        if (fmt->video_codec != AV_CODEC_ID_NONE) {
            AddStream(&video_stream_, fmt->video_codec);
            have_video_ = true;
            encode_video_ = true;
        }
        if (fmt->audio_codec != AV_CODEC_ID_NONE) {
            AddStream(&audio_stream_, fmt->audio_codec);
            have_audio_ = true;
            encode_audio_ = true;
        }

        if (have_video_) {
            OpenVideo(opt);
        }
        if (have_audio_) {
            OpenAudio(opt);
        }

        av_dump_format(output_format_context_, 0, file_path.c_str(), 1);

        // Open the output file, if needed.
        if (!(fmt->flags & AVFMT_NOFILE)) {
            ret = avio_open(&output_format_context_->pb, file_path.c_str(), AVIO_FLAG_WRITE);
            if (ret < 0) {
                LOG(ERROR) << "Could not open " << file_path << ": " << av_err2str(ret);
                return false;
            }
        }
        return true;
    }

    bool FFmpegVideoEncoder::Encode() {
        LOG(INFO) << __FUNCTION__;
        int ret;
        // Write the stream header, if any.
        ret = avformat_write_header(output_format_context_, nullptr);
        if (ret < 0) {
            LOG(ERROR) << "Error occurred when opening output file: " << av_err2str(ret);
            return false;
        }

        while (encode_video_ || encode_audio_) {
            // select the stream to encode
            if (encode_video_ &&
                (!encode_audio_ || av_compare_ts(video_stream_.next_pts, video_stream_.encoder->time_base,
                                                 audio_stream_.next_pts, audio_stream_.encoder->time_base) <= 0)) {
                encode_video_ = WriteVideoFrame();
            } else {
                encode_audio_ = WriteAudioFrame();
            }
        }

        av_write_trailer(output_format_context_);
        return true;
    }

    void FFmpegVideoEncoder::Close() {
        if (have_video_)
            CloseVideoStream();
        if (have_audio_)
            CloseAudioStream();

        if (!(output_format_context_->oformat->flags & AVFMT_NOFILE))
            // Close the output file.
            avio_closep(&output_format_context_->pb);

        // Free the stream.
        avformat_free_context(output_format_context_);
    }

    bool FFmpegVideoEncoder::AddStream(OutputStream* stream,
                                       enum AVCodecID codec_id) {
        AVCodecContext* c;

        // find the encoder
        const AVCodec* codec = avcodec_find_encoder(codec_id);
        if (!codec) {
            LOG(ERROR) << "Could not find encoder for " << avcodec_get_name(codec_id);
            return false;
        }

        stream->temp_packet = av_packet_alloc();
        if (!stream->temp_packet) {
            LOG(ERROR) << "Could not allocate AVPacket";
            return false;
        }

        stream->stream = avformat_new_stream(output_format_context_, nullptr);
        if (!stream->stream) {
            LOG(ERROR) << "Could not allocate stream";
            return false;
        }

        stream->stream->id = int(output_format_context_->nb_streams) - 1;
        c = avcodec_alloc_context3(codec);
        if (!c) {
            LOG(ERROR) << "Could not alloc an encoding context";
            return false;
        }
        stream->encoder = c;

        switch (codec->type) {
            case AVMEDIA_TYPE_AUDIO:
                c->sample_fmt = codec->sample_fmts ?
                                codec->sample_fmts[0] : AV_SAMPLE_FMT_FLTP;
                c->bit_rate = 64000;
                c->sample_rate = 44100;
                if (codec->supported_samplerates) {
                    c->sample_rate = codec->supported_samplerates[0];
                    for (int i = 0; codec->supported_samplerates[i]; i++) {
                        if (codec->supported_samplerates[i] == 44100)
                            c->sample_rate = 44100;
                    }
                }
                c->channel_layout = AV_CH_LAYOUT_STEREO;
                stream->stream->time_base = (AVRational) {1, c->sample_rate};
                break;
            case AVMEDIA_TYPE_VIDEO:
                c->codec_id = codec_id;
                c->bit_rate = 400000;
                c->width = 352;
                c->height = 288;
                stream->stream->time_base = {1, kStreamFrameRate};
                c->time_base = stream->stream->time_base;

                c->gop_size = 12;
                c->pix_fmt = kStreamPixelFormat;
                if (c->codec_id == AV_CODEC_ID_MPEG2VIDEO) {
                    // just for testing, we also add B-frames
                    c->max_b_frames = 2;
                }
                if (c->codec_id == AV_CODEC_ID_MPEG1VIDEO) {
                    // Needed to avoid using macro blocks in which some coefficient overflow.
                    // This does not happen with normal video, it just happens here as
                    // the motion of the chroma plane does not match the luma plane.
                    c->mb_decision = 2;
                }
                break;
            default:
                break;
        }

        // Some formats want stream headers to be separate.
        if (output_format_context_->flags & AVFMT_GLOBALHEADER)
            c->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

        return true;
    }

    // video output
    static AVFrame* AllocFrame(enum AVPixelFormat pix_fmt, int width, int height) {
        AVFrame* frame;
        int ret;

        frame = av_frame_alloc();
        if (!frame)
            return nullptr;

        frame->format = pix_fmt;
        frame->width = width;
        frame->height = height;

        // Allocate the buffer for the frame data.
        ret = av_frame_get_buffer(frame, 0);
        if (ret < 0) {
            LOG(ERROR) << "Could not allocate frame data";
            return nullptr;
        }
        return frame;
    }

    bool FFmpegVideoEncoder::OpenVideo(AVDictionary* opt_arg) {
        AVCodecContext* c = video_stream_.encoder;
        AVDictionary* opt = nullptr;

        av_dict_copy(&opt, opt_arg, 0);

        // open the codec
        int ret = avcodec_open2(c, video_codec_, &opt);
        av_dict_free(&opt);
        if (ret < 0) {
            LOG(ERROR) << "Could not open video codec: " << av_err2str(ret);
            return false;
        }

        // Allocate and init a re-usable frame.
        video_stream_.frame = AllocFrame(c->pix_fmt, c->width, c->height);
        if (!video_stream_.frame) {
            LOG(ERROR) << "Could not allocate video frame";
            return false;
        }

        // If the output format is not YUV420P, then a temporary YUV420P
        // picture is needed too. It is then converted to the required
        // output format.
        video_stream_.temp_frame = nullptr;
        if (c->pix_fmt != AV_PIX_FMT_YUV420P) {
            video_stream_.temp_frame = AllocFrame(AV_PIX_FMT_YUV420P, c->width, c->height);
            if (!video_stream_.temp_frame) {
                LOG(ERROR) << "Could not allocate temporary video frame";
                return false;
            }
        }

        // copy the stream parameters to the muxer
        ret = avcodec_parameters_from_context(video_stream_.stream->codecpar, c);
        if (ret < 0) {
            LOG(ERROR) << "Could not copy the stream parameters";
            return false;
        }
        return true;
    }

    static AVFrame* AllocAudioFrame(enum AVSampleFormat sample_fmt,
                                    uint64_t channel_layout,
                                    int sample_rate,
                                    int nb_samples) {
        AVFrame* frame = av_frame_alloc();
        if (!frame) {
            LOG(ERROR) << "Error allocating an audio frame";
            return nullptr;
        }

        frame->format = sample_fmt;
        frame->channel_layout = channel_layout;
        frame->sample_rate = sample_rate;
        frame->nb_samples = nb_samples;

        if (nb_samples) {
            if (av_frame_get_buffer(frame, 0) < 0) {
                LOG(ERROR) << "Error allocating an audio buffer";
                return nullptr;
            }
        }
        return frame;
    }

    bool FFmpegVideoEncoder::OpenAudio(AVDictionary* opt_arg) {
        AVCodecContext* c;
        int nb_samples;
        int ret;
        AVDictionary* opt = nullptr;

        c = audio_stream_.encoder;

        // open it
        av_dict_copy(&opt, opt_arg, 0);
        ret = avcodec_open2(c, audio_codec_, &opt);
        av_dict_free(&opt);
        if (ret < 0) {
            LOG(ERROR) << "Could not open audio codec: " << av_err2str(ret);
            return false;
        }

        // init signal generator
        audio_stream_.t = 0;
        audio_stream_.cr = float(2.0 * M_PI * 110.0 / c->sample_rate);
        // increment frequency by 110 Hz per second
        audio_stream_.cr2 = float(2.0 * M_PI * 110.0 / c->sample_rate / c->sample_rate);

        if (c->codec->capabilities & AV_CODEC_CAP_VARIABLE_FRAME_SIZE)
            nb_samples = 10000;
        else
            nb_samples = c->frame_size;

        audio_stream_.frame = AllocAudioFrame(c->sample_fmt,
                                              c->channel_layout,
                                              c->sample_rate,
                                              nb_samples);
        audio_stream_.temp_frame = AllocAudioFrame(AV_SAMPLE_FMT_S16,
                                                   c->channel_layout,
                                                   c->sample_rate,
                                                   nb_samples);

        // copy the stream parameters to the muxer
        ret = avcodec_parameters_from_context(audio_stream_.stream->codecpar, c);
        if (ret < 0) {
            LOG(ERROR) << "Could not copy the stream parameters";
            return false;
        }

        // create resampler context
        audio_stream_.swr_context = swr_alloc_set_opts(nullptr,
                                                       int64_t(c->channel_layout),
                                                       c->sample_fmt,
                                                       c->sample_rate,
                                                       int64_t(c->channel_layout),
                                                       AV_SAMPLE_FMT_S16,
                                                       c->sample_rate,
                                                       0,
                                                       nullptr);

        // initialize the resampling context
        if (swr_init(audio_stream_.swr_context) < 0) {
            LOG(ERROR) << "Failed to initialize the resampling context";
            return false;
        }

        return true;
    }

    static void LogPacket(const AVFormatContext* format_context,
                          const AVPacket* pkt) {
        AVRational* time_base = &format_context->streams[pkt->stream_index]->time_base;
        printf("pts: %s pts_time: %s dts: %s dts_time: %s duration: %s duration_time: %s stream_index: %d\n",
               av_ts2str(pkt->pts), av_ts2timestr(pkt->pts, time_base),
               av_ts2str(pkt->dts), av_ts2timestr(pkt->dts, time_base),
               av_ts2str(pkt->duration), av_ts2timestr(pkt->duration, time_base),
               pkt->stream_index);
    }

    bool FFmpegVideoEncoder::WriteFrame(OutputStream* ost,
                                        AVFrame* frame,
                                        AVPacket* packet) {
        int ret;

        // send the frame to the encoder
        ret = avcodec_send_frame(ost->encoder, frame);
        if (ret < 0) {
            // LOG(ERROR) << "Error sending a frame to the encoder";
            return false;
        }

        while (ret >= 0) {
            ret = avcodec_receive_packet(ost->encoder, packet);
            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                return true;
            else if (ret < 0) {
                LOG(ERROR) << "Error encoding a frame";
                return false;
            }

            // Rescale output packet timestamp values from codec to stream timebase.
            av_packet_rescale_ts(packet, ost->encoder->time_base, ost->stream->time_base);
            packet->stream_index = ost->stream->index;

            // Write the compressed frame to the media file.
            LogPacket(output_format_context_, packet);
            ret = av_interleaved_write_frame(output_format_context_, packet);
            if (ret < 0) {
                LOG(ERROR) << "Error while writing output packet";
                return false;
            }
        }
        return false;
    }

    // Prepare a dummy image.
    static void FillYUVImage(AVFrame* frame, int64_t frame_index,
                             int width, int height) {
        int x, y;
        int64_t i = frame_index;

        // Y
        for (y = 0; y < height; y++)
            for (x = 0; x < width; x++)
                frame->data[0][y * frame->linesize[0] + x] = x + y + i * 3;

        // Cb and Cr
        for (y = 0; y < height / 2; y++) {
            for (x = 0; x < width / 2; x++) {
                frame->data[1][y * frame->linesize[1] + x] = 128 + y + i * 2;
                frame->data[2][y * frame->linesize[2] + x] = 64 + x + i * 5;
            }
        }
    }

    AVFrame* FFmpegVideoEncoder::GetVideoFrame() {
        // Check if we want to generate more frames.
        if (av_compare_ts(video_stream_.next_pts, video_stream_.encoder->time_base,
                          kStreamDuration, {1, 1}) > 0) {
            return nullptr;
        }

        // When we pass a frame to the encoder, it may keep a reference to it
        // internally; make sure we do not overwrite it here.
        if (av_frame_make_writable(video_stream_.frame) < 0)
            return nullptr;

        if (video_stream_.encoder->pix_fmt != AV_PIX_FMT_YUV420P) {
            // As we only generate a YUV420P picture, we must convert it
            // to the codec pixel format if needed.
            if (!video_stream_.sws_context) {
                video_stream_.sws_context = sws_getContext(video_stream_.encoder->width,
                                                           video_stream_.encoder->height,
                                                           AV_PIX_FMT_YUV420P,
                                                           video_stream_.encoder->width,
                                                           video_stream_.encoder->height,
                                                           video_stream_.encoder->pix_fmt,
                                                           SWS_BICUBIC,
                                                           nullptr,
                                                           nullptr,
                                                           nullptr);
                if (!video_stream_.sws_context) {
                    LOG(ERROR) << "Could not initialize the conversion context";
                    return nullptr;
                }
            }
            FillYUVImage(video_stream_.temp_frame,
                         video_stream_.next_pts,
                         video_stream_.encoder->width,
                         video_stream_.encoder->height);
            sws_scale(video_stream_.sws_context, (const uint8_t* const*) video_stream_.temp_frame->data,
                      video_stream_.temp_frame->linesize, 0,
                      video_stream_.encoder->height,
                      video_stream_.frame->data,
                      video_stream_.frame->linesize);
        } else {
            FillYUVImage(video_stream_.frame, video_stream_.next_pts,
                         video_stream_.encoder->width,
                         video_stream_.encoder->height);
        }

        video_stream_.frame->pts = video_stream_.next_pts++;
        return video_stream_.frame;
    }

    // Encode one video frame and send it to the muxer.
    // return true when encoding is finished, false otherwise.
    bool FFmpegVideoEncoder::WriteVideoFrame() {
        return WriteFrame(&video_stream_, GetVideoFrame(), video_stream_.temp_packet);
    }

    static AVFrame* GetAudioFrame(OutputStream* ost) {
        AVFrame* frame = ost->temp_frame;
        int i, j, v;
        auto* q = (int16_t*) frame->data[0];

        // check if we want to generate more frames
        if (av_compare_ts(ost->next_pts, ost->encoder->time_base,
                          kStreamDuration, {1, 1}) > 0)
            return nullptr;

        for (j = 0; j < frame->nb_samples; j++) {
            v = (int) (sin(ost->t) * 10000);
            for (i = 0; i < ost->encoder->channels; i++)
                *q++ = int16_t(v);
            ost->t += ost->cr;
            ost->cr += ost->cr2;
        }

        frame->pts = ost->next_pts;
        ost->next_pts += frame->nb_samples;

        return frame;
    }

    // Encode one audio frame and send it to the muxer.
    // return true when encoding is finished, false otherwise.
    bool FFmpegVideoEncoder::WriteAudioFrame() {
        AVFrame* frame = GetAudioFrame(&audio_stream_);
        int dst_nb_samples;
        int ret;
        if (frame) {
            dst_nb_samples = av_rescale_rnd(swr_get_delay(audio_stream_.swr_context,
                                                          audio_stream_.encoder->sample_rate) + frame->nb_samples,
                                            audio_stream_.encoder->sample_rate,
                                            audio_stream_.encoder->sample_rate,
                                            AV_ROUND_UP);

            ret = av_frame_make_writable(audio_stream_.frame);
            if (ret < 0)
                return false;

            // convert to destination format
            ret = swr_convert(audio_stream_.swr_context,
                              audio_stream_.frame->data,
                              dst_nb_samples,
                              (const uint8_t**) frame->data,
                              frame->nb_samples);
            if (ret < 0) {
                LOG(ERROR) << "Error while converting";
                return false;
            }
            frame = audio_stream_.frame;
            frame->pts = av_rescale_q(audio_stream_.samples_count,
                                      {1, audio_stream_.encoder->sample_rate},
                                      audio_stream_.encoder->time_base);
            audio_stream_.samples_count += dst_nb_samples;
        }

        return WriteFrame(&audio_stream_, frame, audio_stream_.temp_packet);
    }

    void FFmpegVideoEncoder::CloseVideoStream() {

    }

    void FFmpegVideoEncoder::CloseAudioStream() {

    }
}
