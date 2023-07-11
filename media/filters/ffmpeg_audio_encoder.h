//
// Created by wangrl2016 on 2023/6/12.
//

#ifndef CHARACTER_FFMPEG_AUDIO_ENCODER_H
#define CHARACTER_FFMPEG_AUDIO_ENCODER_H

#include <string>
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include <libavutil/audio_fifo.h>
}
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

    private:
        AVFormatContext* output_format_context_ = nullptr;
        AVCodecContext* output_codec_context_ = nullptr;
        SwrContext* resampler_context_ = nullptr;
        AVAudioFifo* fifo_ = nullptr;

        bool open_succeed;
    };
}

#endif //CHARACTER_FFMPEG_AUDIO_ENCODER_H
