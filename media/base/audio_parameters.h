//
// Created by wangrl2016 on 2023/6/2.
//

#ifndef CHARACTER_AUDIO_PARAMETERS_H
#define CHARACTER_AUDIO_PARAMETERS_H

extern "C" {
#include <libavutil/samplefmt.h>
}

namespace media {
    class AudioParameters {
    public:
        AudioParameters() = default;

        AudioParameters(int sample_rate,
                        int channel_count,
                        AVSampleFormat sample_format);

        [[nodiscard]] int sample_rate() const { return sample_rate_; }

        void set_sample_rate(int sample_rate) {
            sample_rate_ = sample_rate;
        }

        [[nodiscard]] int channel_count() const { return channel_count_; }

        void set_channel_count(int channel_count) {
            channel_count_ = channel_count;
        }

        [[nodiscard]] AVSampleFormat sample_format() const { return sample_format_; }

        void set_sample_format(AVSampleFormat sample_format) {
            sample_format_ = sample_format;
        }

        [[nodiscard]] int frames_per_buffer() const { return frames_per_buffer_; }

        void set_frames_per_buffer(int frames_per_buffer) {
            frames_per_buffer_ = frames_per_buffer;
        }

        void SetParams(int sample_rate,
                       int channel_count,
                       AVSampleFormat sample_format);

        bool IsValid() const;

    private:
        int sample_rate_ = -1;
        int channel_count_ = -1;
        AVSampleFormat sample_format_ = AV_SAMPLE_FMT_NONE;
        int frames_per_buffer_;
    };
}

#endif //CHARACTER_AUDIO_PARAMETERS_H
