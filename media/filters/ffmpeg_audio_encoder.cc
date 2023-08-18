//
// Created by wangrl2016 on 2023/6/12.
//

#include <glog/logging.h>
#include "media/filters/ffmpeg_audio_encoder.h"

namespace media {
    // The output bit rate in bit/s
    #define kOutputBitRate 96000

    FFmpegAudioEncoder::FFmpegAudioEncoder(base::FilePath& file_path,
                                           AudioParameters& src_parameters,
                                           AudioParameters& dest_parameters) {
        open_succeed_ = Open(file_path, src_parameters, dest_parameters);
    }

    bool FFmpegAudioEncoder::Open(base::FilePath& file_path,
                             AudioParameters& src_parameters,
                             AudioParameters& dest_parameters) {
        const AVCodec* codec = nullptr;
        // Open the output file to write to it.
        AVIOContext* output_io_context = nullptr;

        if (avio_open(&output_io_context, file_path.value().c_str(), AVIO_FLAG_WRITE) < 0) {
            LOG(ERROR) << "Could not open output file " << file_path;
            return false;
        }

        // Create a new format context for the output container format.
        if (!(output_format_context_ = avformat_alloc_context())) {
            LOG(ERROR) << "Could not allocate output format context\n";
            return false;
        }

        // Associate the output file (pointer) with the container format context.
        output_format_context_->pb = output_io_context;

        // Guess the desired container format based on the file extension.
        if (!(output_format_context_->oformat = av_guess_format(nullptr,
                                                                file_path.value().c_str(),
                                                                nullptr))) {
            LOG(ERROR) << "Could not find output file format";
            return false;
        }

        if (!(output_format_context_->url = av_strdup(file_path.value().c_str()))) {
            LOG(ERROR) << "Could not allocate url";
            return false;
        }

        auto extension = file_path.FinalExtension();
        // Find the encoder to be used by its name.
        if (extension == FILE_PATH_LITERAL("wav")) {
            if (!(codec = avcodec_find_encoder(AV_CODEC_ID_PCM_F32LE))) {
                return false;
            }
        } else if (extension == FILE_PATH_LITERAL("mp3")) {
            if (!(codec = avcodec_find_encoder(AV_CODEC_ID_MP3))) {
                return false;
            }
        } else if (extension == FILE_PATH_LITERAL("m4a")) {
            if (!(codec = avcodec_find_encoder(AV_CODEC_ID_AAC))) {
                return false;
            }
        }

        // Create a new audio stream in the output file container.
        if (!(stream_ = avformat_new_stream(output_format_context_, nullptr))) {
            LOG(ERROR) << "Could not create new stream";
            return false;
        }

        if (!(output_codec_context_ = avcodec_alloc_context3(codec))) {
            LOG(ERROR) << "Could not allocate an encoding context";
            return false;
        }

        // set the basic encoder parameters.
        // The input file's sample rate is used to avoid a sample rate conversion.
        output_codec_context_->channels = dest_parameters.channel_count();
        output_codec_context_->channel_layout =
                uint64_t(av_get_default_channel_layout(dest_parameters.channel_count()));
        output_codec_context_->sample_rate = dest_parameters.sample_rate();
        output_codec_context_->sample_fmt = dest_parameters.sample_format();
        output_codec_context_->bit_rate = kOutputBitRate;

        // Set the sample rate for the container.
        stream_->time_base.den = dest_parameters.sample_rate();
        stream_->time_base.num = 1;

        // Some container formats (like MP4) require global headers to be present.
        // Mark the encoder so that it behaves accordingly.
        if (output_format_context_->oformat->flags & AVFMT_GLOBALHEADER)
            output_codec_context_->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

        // Open the encoder for the audio stream to use it later.
        if (avcodec_open2(output_codec_context_, codec, nullptr) < 0) {
            LOG(ERROR) << "Could not open output codec";
            return false;
        }

        if (avcodec_parameters_from_context(stream_->codecpar, output_codec_context_) < 0) {
            LOG(ERROR) << "Could not initialize stream parameters";
            return false;
        }

        // Create a resampler context for the conversion.
        resampler_context_ = swr_alloc_set_opts(
                nullptr,
                av_get_default_channel_layout(output_codec_context_->channels),
                output_codec_context_->sample_fmt,
                output_codec_context_->sample_rate,
                av_get_default_channel_layout(src_parameters.channel_count()),
                src_parameters.sample_format(),
                src_parameters.sample_rate(),
                0,
                nullptr);

        // Open the resampler with the specified parameters.
        if (swr_init(resampler_context_) < 0) {
            LOG(ERROR) << "Could not open resample context";
            return false;
        }

        return true;

    }
}
