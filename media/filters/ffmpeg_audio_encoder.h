//
// Created by wangrl2016 on 2023/6/12.
//

#ifndef CHARACTER_FFMPEG_AUDIO_ENCODER_H
#define CHARACTER_FFMPEG_AUDIO_ENCODER_H

#include <string>
#include "media/base/audio_parameters.h"

namespace media {
    class FFmpegAudioEncoder {
    public:
        FFmpegAudioEncoder(const std::string& file_path,
                           AudioParameters& src_parameters,
                           AudioParameters& dest_parameters);

        ~FFmpegAudioEncoder();

        bool Open(const std::string& file_path,
                  AudioParameters& src_parameters,
                  AudioParameters& dest_parameters);
    };
}

#endif //CHARACTER_FFMPEG_AUDIO_ENCODER_H
