//
// Created by wangrl2016 on 2023/6/3.
//

#include <glog/logging.h>
#include "media/base/audio_bus.h"
#include "audio_constant.h"

namespace media {
    static bool IsAligned(void* ptr) {
        return (reinterpret_cast<uintptr_t>(ptr) &
                (AudioBus::kChannelAlignment - 1)) == 0U;
    }

    static int CalculateMemorySizeInternal(int channels,
                                           int frames,
                                           int* out_aligned_frames) {
        // Since our internal sample format is float, we can guarantee the alignment
        // by making the number of frames an integer multiple of
        // AudioBus::kChannelAlignment / sizeof(float).
        int aligned_frames =
                ((frames * int(sizeof(float)) + AudioBus::kChannelAlignment - 1) &
                 ~(AudioBus::kChannelAlignment - 1)) / int(sizeof(float));

        if (out_aligned_frames)
            *out_aligned_frames = aligned_frames;

        return int(sizeof(float)) * channels * aligned_frames;
    }

    static void ValidateConfig(int channels, int frames) {
        CHECK_GT(frames, 0);
        CHECK_GT(channels, 0);
        CHECK_LE(channels, kMaxChannels);
    }

    AudioBus::AudioBus(int channels, int frames) :
            frames_(frames) {
        int aligned_frames = 0;
        int size = CalculateMemorySizeInternal(channels, frames, &aligned_frames);
        data_.reset(static_cast<float*>(base::AlignedAlloc(
                size, AudioBus::kChannelAlignment)));

        BuildChannelData(channels, aligned_frames, data_.get());
    }

    AudioBus::AudioBus(int channels, int frames, float* data) :
            frames_(frames) {
        // Since |data| may have come from an external source, ensure it's valid.
        CHECK(data);
        ValidateConfig(channels, frames_);

        int aligned_frames = 0;
        CalculateMemorySizeInternal(channels, frames, &aligned_frames);

        BuildChannelData(channels, aligned_frames, data);
    }

    AudioBus::AudioBus(int frames, const std::vector<float*>& channel_data) :
            channel_data_(channel_data),
            frames_(frames) {
        ValidateConfig(int(channel_data_.size()), frames_);

        // Sanity check wrapped vector for alignment and channel count.
        for (size_t i = 0; i < channel_data.size(); i++) {
            DCHECK(IsAligned(channel_data_[i]));
        }
    }

    std::unique_ptr<AudioBus> AudioBus::Create(int channels, int frames) {
        return std::unique_ptr<AudioBus>(new AudioBus(channels, frames));
    }

    std::unique_ptr<AudioBus> AudioBus::Create(const AudioParameters& params) {
        return std::unique_ptr<AudioBus>(
                new AudioBus(params.channel_count(),
                             params.frames_per_buffer()));
    }

    void AudioBus::BuildChannelData(int channels, int aligned_frames, float* data) {
        DCHECK(IsAligned(data));
        DCHECK_EQ(channel_data_.size(), 0U);
        // Initialize |channel_data_| with pointers into |data|.
        channel_data_.reserve(channels);
        for (int i = 0; i < channels; i++) {
            channel_data_.push_back(data + i * aligned_frames);
        }
    }
}
