//
// Created by wangrl2016 on 2023/6/1.
//

#include <glog/logging.h>
#include "media/filters/ffmpeg_audio_decoder.h"

// Reference:
// http://ffmpeg.org/doxygen/trunk/demux_decode_8c-example.html
// http://ffmpeg.org/doxygen/trunk/resample_audio_8c-example.html

namespace media {
    FFmpegAudioDecoder::FFmpegAudioDecoder(const AudioParameters& dest_params) :
            dest_params_(dest_params) {}

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

            // Find decoder for the stream.
            const AVCodec* decoder = avcodec_find_decoder(stream->codecpar->codec_id);
            if (!decoder) {
                LOG(ERROR) << "Failed to find " << av_get_media_type_string(AVMEDIA_TYPE_AUDIO)
                           << " codec";
                Close();
                return false;
            }

            // Allocate a codec context for the decoder.
            decoder_context_ = avcodec_alloc_context3(decoder);
            if (!decoder_context_) {
                LOG(ERROR) << "Failed to allocate the " << av_get_media_type_string(AVMEDIA_TYPE_AUDIO)
                           << " codec context";
                Close();
                return false;
            }

            // Copy codec parameters from input stream to output codec context.
            if (avcodec_parameters_to_context(decoder_context_, stream->codecpar) < 0) {
                LOG(ERROR) << "Failed to copy " << av_get_media_type_string(AVMEDIA_TYPE_AUDIO)
                           << " codec parameters to decoder context";
                Close();
                return false;
            }

            // Init the decoders.
            if (avcodec_open2(decoder_context_, decoder, nullptr) < 0) {
                LOG(ERROR) << "Failed to open " << av_get_media_type_string(AVMEDIA_TYPE_AUDIO)
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

        return true;
    }

    bool FFmpegAudioDecoder::OpenFromMemory(const uint8_t* data, size_t size) {

        return true;
    }

    void FFmpegAudioDecoder::Close() {

    }
}
