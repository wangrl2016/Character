//
// Created by wangrl2016 on 2023/6/1.
//

#include <glog/logging.h>
#include "media/filters/ffmpeg_audio_decoder.h"

// Reference:
// http://ffmpeg.org/doxygen/trunk/demux_decode_8c-example.html
// http://ffmpeg.org/doxygen/trunk/resample_audio_8c-example.html

namespace media {
    // AAC(M4A) decoding specific constants.
    static const int kAACPrimingFrameCount = 2112;
    static const int kAACRemainderFrameCount = 519;

    static const AVRational kMicrosBase = {1, base::kMicrosecondsPerSecond};

    FFmpegAudioDecoder::FFmpegAudioDecoder(const AudioParameters& dest_params) :
            dest_params_(dest_params) {
        CHECK_EQ(dest_params.sample_format(), AV_SAMPLE_FMT_FLT);
    }

    bool FFmpegAudioDecoder::OpenFromFile(const std::string& file_path) {
        // Open input file, and allocate format context.
        if (avformat_open_input(&format_context_,
                                file_path.c_str(),
                                nullptr,
                                nullptr)) {
            LOG(ERROR) << "Could not open source file " << file_path;
            Close();
            return false;
        }

        // Retrieve stream information.
        if (avformat_find_stream_info(format_context_, nullptr) < 0) {
            LOG(ERROR) << "Could not find stream information";
            Close();
            return false;
        }

        audio_stream_index_ = av_find_best_stream(format_context_,
                                                  AVMEDIA_TYPE_AUDIO,
                                                  -1,
                                                  -1,
                                                  nullptr,
                                                  0);
        if (audio_stream_index_ < 0) {
            LOG(ERROR) << "Could not find audio stream in input file " << file_path;
            Close();
            return false;
        } else {
            AVStream* stream = format_context_->streams[audio_stream_index_];

            if (stream->disposition & AV_DISPOSITION_ATTACHED_PIC) {
                attached_pic_ = std::make_unique<AVPacket>(stream->attached_pic);
            }

            // Find decoder for the stream.
            const AVCodec* decoder = avcodec_find_decoder(stream->codecpar->codec_id);
            if (!decoder) {
                LOG(ERROR) << "Failed to find "
                           << av_get_media_type_string(AVMEDIA_TYPE_AUDIO)
                           << " codec";
                Close();
                return false;
            }

            // Allocate a codec context for the decoder.
            decoder_context_ = avcodec_alloc_context3(decoder);
            if (!decoder_context_) {
                LOG(ERROR) << "Failed to allocate the "
                           << av_get_media_type_string(AVMEDIA_TYPE_AUDIO)
                           << " codec context";
                Close();
                return false;
            }

            // Copy codec parameters from input stream to output codec context.
            if (avcodec_parameters_to_context(decoder_context_, stream->codecpar) < 0) {
                LOG(ERROR) << "Failed to copy "
                           << av_get_media_type_string(AVMEDIA_TYPE_AUDIO)
                           << " codec parameters to decoder context";
                Close();
                return false;
            }

            // Init the decoders.
            if (avcodec_open2(decoder_context_, decoder, nullptr) < 0) {
                LOG(ERROR) << "Failed to open "
                           << av_get_media_type_string(AVMEDIA_TYPE_AUDIO)
                           << " codec";
                Close();
                return false;
            }
        }

        if (dest_params_.IsValid()) {
            if (decoder_context_->sample_rate != dest_params_.sample_rate() ||
                decoder_context_->channels != dest_params_.channel_count() ||
                decoder_context_->sample_fmt != dest_params_.sample_format()) {
                // Create a resampler context for the conversion.
                // Set the conversion parameters.
                swr_context_ = swr_alloc_set_opts(
                        nullptr,
                        av_get_default_channel_layout(
                                dest_params_.channel_count()),
                        dest_params_.sample_format(),
                        dest_params_.sample_rate(),
                        int64_t(decoder_context_->channel_layout),
                        decoder_context_->sample_fmt,
                        decoder_context_->sample_rate,
                        0,
                        nullptr);
                if (!swr_context_) {
                    LOG(ERROR) << "Could not allocate resample context";
                    Close();
                    return false;
                }

                // Open the resampler with the specified parameters.
                if (swr_init(swr_context_) < 0) {
                    LOG(ERROR) << "Could not open resample context";
                    Close();
                    return false;
                }
            }
        }

        const AVDictionaryEntry* tag = nullptr;
        while ((tag = av_dict_get(format_context_->metadata,
                                  "",
                                  tag,
                                  AV_DICT_IGNORE_SUFFIX))) {
            metadata_.push_back({tag->key, tag->value});
        }

        // Dump input information.
        av_dump_format(format_context_,
                       audio_stream_index_,
                       file_path.c_str(),
                       0);

        return true;
    }

    bool FFmpegAudioDecoder::OpenFromMemory(const uint8_t* data, size_t size) {

        return true;
    }

    bool FFmpegAudioDecoder::HasKnownDuration() const {
        return format_context_->duration != AV_NOPTS_VALUE;
    }

    base::TimeDelta FFmpegAudioDecoder::GetDuration() const {
        const AVRational av_time_base = {1, AV_TIME_BASE};
        DCHECK_LE(format_context_->duration, AV_NOPTS_VALUE);

        int64_t estimated_duration_us = format_context_->duration;

        if (decoder_context_->codec_id == AV_CODEC_ID_AAC) {
            // For certain AAC-encoded files, FFmpeg estimated frame count might not
            // be sufficient to capture the entire audio content that we want. This is
            // especially noticeable for short files (< 10ms) resulting in silence
            // throughout the decoded buffer. Thus, we add the priming frames and the
            // remainder frames to the estimation.
            estimated_duration_us += std::ceil(
                    1000000.0 * static_cast<double>(kAACPrimingFrameCount + kAACRemainderFrameCount) /
                    SourceSampleRate());
        } else {
            // Add one microsecond to avoid rounding-down errors which can occur when
            // |duration| has been calculated from an exact number of sample-frames.
            // One microsecond is much less than the time of a single sample-frame
            // at any real-world sample-rate.
            estimated_duration_us += 1;
        }

        int64_t microseconds = av_rescale_q(estimated_duration_us,
                                            av_time_base,
                                            kMicrosBase);
        return base::Microseconds(microseconds);
    }

    int FFmpegAudioDecoder::GetNumberOfFrames() const {
        return int(GetDuration().InSecondsF() * dest_params_.sample_rate());
    }

    std::unique_ptr<AudioBus> FFmpegAudioDecoder::ReadFrames(int frames_to_read) {
        total_count_ = GetNumberOfFrames();
        if (total_count_ > frames_to_read)
            total_count_ = frames_to_read;
        std::unique_ptr<AudioBus> audio_bus = AudioBus::Create(
                dest_params_.channel_count(), total_count_);


        AVPacket* packet = av_packet_alloc();
        if (!packet) {
            LOG(ERROR) << "Error allocating an audio packet";
            return nullptr;
        }

        AVFrame* frame = av_frame_alloc();
        if (!frame) {
            LOG(ERROR) << "Error allocating an audio frame";
            return nullptr;
        }

        int ret;
        while (av_read_frame(format_context_, packet) >= 0) {
            if (packet->stream_index == audio_stream_index_) {
                ret = DecodePacket(audio_bus, packet, frame);
            }

            av_packet_unref(packet);
            if (ret < 0)
                break;
        }

        // Flush the decoders.
        if (decoder_context_) {
            DecodePacket(audio_bus, nullptr, frame);
        }

        return audio_bus;
    }

    void FFmpegAudioDecoder::Close() {
        if (dst_data_) {
            av_freep(&dst_data_[0]);
        }
        av_freep(dst_data_);
        if (swr_context_) {
            swr_free(&swr_context_);
        }
        if (decoder_context_) {
            avcodec_free_context(&decoder_context_);
            decoder_context_ = nullptr;
        }
        if (format_context_) {
            avformat_close_input(&format_context_);
            format_context_ = nullptr;
        }
    }

    int FFmpegAudioDecoder::DecodePacket(std::unique_ptr<AudioBus>& audio_bus,
                                         const AVPacket* packet,
                                         AVFrame* frame) {
        // Submit the packet to the decoder.
        int ret = avcodec_send_packet(decoder_context_, packet);
        if (ret < 0) {
            LOG(ERROR) << "Error submitting a packet for decoding";
            return ret;
        }

        // Get all the available frames from the decoder.
        while (true) {
            ret = avcodec_receive_frame(decoder_context_, frame);
            if (ret < 0) {
                // Those two return values are special and mean there is no output
                // frame available, but there were no errors during decoding.
                if (ret == AVERROR_EOF || ret == AVERROR(EAGAIN))
                    return 0;
                LOG(INFO) << "Error during decoding " << ret;
                return ret;
            }

            // Write the frame data to the AudioBus.
            // Compute destination number of samples.
            int frames_to_write = 0;
            if (swr_context_) {
                int dst_nb_samples = int(av_rescale_rnd(
                        swr_get_delay(swr_context_,
                                      SourceSampleRate()) + frame->nb_samples,
                        dest_params_.sample_rate(),
                        SourceSampleRate(),
                        AV_ROUND_UP));
                if (dst_nb_samples > max_dst_nb_samples_) {
                    if (dst_data_) {
                        av_freep(&dst_data_[0]);
                    }
                    ret = av_samples_alloc(dst_data_,
                                           &dst_line_size_,
                                           dest_params_.channel_count(),
                                           dst_nb_samples,
                                           dest_params_.sample_format(),
                                           1 /* no align */);
                    if (ret < 0) {
                        av_frame_unref(frame);
                        break;
                    }

                    max_dst_nb_samples_ = dst_nb_samples;
                }

                // Convert to destination format.
                ret = swr_convert(swr_context_,
                                  dst_data_,
                                  dst_nb_samples,
                                  (const uint8_t**) frame->data,
                                  frame->nb_samples);

                if (ret > 0) {
                    frames_to_write = ret;
                    frames_to_write = total_count_ - decoded_count_ > frames_to_write ?
                                      frames_to_write : total_count_ - decoded_count_;

                    audio_bus->FromInterleavedPartial(
                            (const float*) dst_data_,
                            decoded_count_,
                            frames_to_write);
                }
            } else {
                // no resampler
                if (total_count_ > decoded_count_) {
                    frames_to_write = frame->nb_samples;
                    frames_to_write = total_count_ - decoded_count_ > frames_to_write ?
                                      frames_to_write : total_count_ - decoded_count_;

                    audio_bus->FromInterleavedPartial(
                            (const float*) frame->data[0],
                            decoded_count_,
                            frames_to_write);
                } else {
                    ret = -1;
                }
            }

            decoded_count_ += frames_to_write;
            av_frame_unref(frame);

            if (ret < 0)
                return ret;
        }

        return 0;
    }
}
