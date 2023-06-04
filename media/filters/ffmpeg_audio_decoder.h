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
#include "base/time/time_delta.h"

namespace media {
    // Demux, decoder, resample audio.
    class FFmpegAudioDecoder {
    public:
        FFmpegAudioDecoder() = default;

        explicit FFmpegAudioDecoder(const AudioParameters& dest_params);

        ~FFmpegAudioDecoder() = default;

        bool OpenFromFile(const std::string& file_path);

        bool OpenFromMemory(const uint8_t* data, size_t size);

        [[nodiscard]] int SourceSampleRate() const {
            return decoder_context_->sample_rate;
        }

        [[nodiscard]] int SourceChannelCount() const {
            return decoder_context_->channels;
        }

        AVSampleFormat SourceSampleFormat() {
            return decoder_context_->sample_fmt;
        }

        // Returns true if (an estimated) duration of the audio data is
        // known. Must be called after Open().
        [[nodiscard]] bool HasKnownDuration() const;

        // Please note that GetDuration() and GetNumberOfFrames() attempt to be
        // accurate, but are only estimates. For some encoded formats, the actual
        // duration of the file can only be determined once all the file data has been
        // read. The ReadAllFrames() method returns the actual number of
        // sample-frames it has read.
        [[nodiscard]] base::TimeDelta GetDuration() const;

        [[nodiscard]] int GetNumberOfFrames() const;

        // The audio data will be decoded as floating-point linear.
        // If |frames_to_read| is std::numeric_limits<int>::max(), decodes the entire
        // data.
        std::unique_ptr<AudioBus> ReadFrames(int frames_to_read =
                std::numeric_limits<int>::max());

        void Close();

    private:
        int DecodePacket(std::unique_ptr<AudioBus>& audio_bus,
                         const AVPacket* packet, AVFrame* frame);

        AudioParameters dest_params_;

        AVFormatContext* format_context_ = nullptr;
        AVCodecContext* decoder_context_ = nullptr;
        SwrContext* swr_context_ = nullptr;
        int audio_stream_index_ = -1;

        int max_dst_nb_samples_ = -1;
        uint8_t** dst_data_ = nullptr;
        int dst_line_size_ = 0;

        // Read frames from the audio.
        int decoded_count_ = 0;
        int total_count_ = 0;
    };
}

#endif //CHARACTER_FFMPEG_AUDIO_DECODER_H
