//
// Created by wangrl2016 on 2023/6/29.
//

#include <glog/logging.h>
#include "media/filters/ffmpeg_video_encoder.h"

namespace media {
    constexpr int kStreamFrameRate = 25;
    constexpr AVPixelFormat kStreamPixelFormat = AV_PIX_FMT_YUV420P;

    FFmpegVideoEncoder::FFmpegVideoEncoder() {

    }

    FFmpegVideoEncoder::~FFmpegVideoEncoder() {

    }

    bool FFmpegVideoEncoder::Open(std::string file_path) {
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
            AddStream(&video_stream_, fmt->audio_codec);
        }

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
}
