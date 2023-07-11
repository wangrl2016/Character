//
// Created by wangrl2016 on 2023/6/12.
//

#include <glog/logging.h>
#include "media/filters/ffmpeg_audio_encoder.h"

namespace media {
    FFmpegAudioEncoder::FFmpegAudioEncoder(const std::string& file_path,
                                           AudioParameters& src_parameters,
                                           AudioParameters& dest_parameters) {
        Open(file_path, src_parameters, dest_parameters);
    }

    bool FFmpegAudioEncoder::Open(const std::string& file_path,
                             AudioParameters& src_parameters,
                             AudioParameters& dest_parameters) {
        int ret;
        // Open the output file to write to it.
        AVIOContext* output_io_context = nullptr;
        if (avio_open(&output_io_context, file_path.c_str(), AVIO_FLAG_WRITE) < 0) {
            LOG(ERROR) << "Could not open output file " << file_path;
            return false;
        }

        // Create a new format context for the output container format.
        if (avformat_alloc_output_context2(&output_format_context_,
                                       nullptr,
                                       nullptr,
                                       file_path.c_str()) < 0) {
            LOG(INFO) << "Could not deduce output format from file extension.";
            return false;
        }

        // Associate the output file (pointer) with the container format context.
        output_format_context_->pb = output_io_context;


        return true;

    }
}
