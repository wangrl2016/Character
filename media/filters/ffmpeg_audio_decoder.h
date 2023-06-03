//
// Created by wangrl2016 on 2023/6/1.
//

#ifndef CHARACTER_FFMPEG_AUDIO_DECODER_H
#define CHARACTER_FFMPEG_AUDIO_DECODER_H

#include <string>
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
}
#include "media/base/audio_bus.h"
#include "media/base/audio_parameters.h"

namespace media {
    // Demux, decoder, resample audio.
    class FFmpegAudioDecoder {
    public:
        FFmpegAudioDecoder() = default;

        explicit FFmpegAudioDecoder(const AudioParameters& dest_params);

        ~FFmpegAudioDecoder() = default;

        bool OpenFromFile(const std::string& file_path);

        bool OpenFromMemory(const uint8_t* data, size_t size);

        int SourceSampleRate() {
            return decoder_context_->sample_rate;
        }

        int SourceChannelCount() {
            return decoder_context_->channels;
        }

        AVSampleFormat SourceSampleFormat() {
            return decoder_context_->sample_fmt;
        }

        int64_t ReadAllFrames(AudioBus audio_bus);

        void Close();

    private:
        AudioParameters dest_params_;

        AVFormatContext* format_context_ = nullptr;
        AVCodecContext* decoder_context_ = nullptr;
        SwrContext* swr_context_ = nullptr;
        int audio_stream_index_ = -1;
    };
}

#endif //CHARACTER_FFMPEG_AUDIO_DECODER_H
