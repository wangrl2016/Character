//
// Created by wangrl2016 on 2023/6/12.
//

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
        // Open the output file to write to it.
        int error;

        return true;

    }
}
