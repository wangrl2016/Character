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

    void AudioBus::CheckOverflow(int start_frame, int frames, int total_frames) {
        CHECK_GE(start_frame, 0);
        CHECK_GE(frames, 0);
        CHECK_GT(total_frames, 0);
        int sum = start_frame + frames;
        CHECK_LE(sum, total_frames);
        CHECK_GE(sum, 0);
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

    std::unique_ptr<AudioBus> AudioBus::WrapVector(int frames,
                                                   const std::vector<float*>& channel_data) {
        return std::unique_ptr<AudioBus>(
                new AudioBus(frames, channel_data));
    }

    std::unique_ptr<AudioBus> AudioBus::WrapMemory(int channels, int frames, void* data) {
        // |data| must be aligned by AudioBus::kChannelAlignment.
        CHECK(IsAligned(data));
        return std::unique_ptr<AudioBus>(
                new AudioBus(channels, frames, static_cast<float*>(data)));
    }

    std::unique_ptr<AudioBus> AudioBus::WrapMemory(const AudioParameters& params,
                                                   void* data) {
        // |data| must be aligned by AudioBus::kChannelAlignment.
        CHECK(IsAligned(data));
        return std::unique_ptr<AudioBus>(
                new AudioBus(params.channel_count(),
                             params.frames_per_buffer(),
                             static_cast<float*>(data)));
    }

    int AudioBus::CalculateMemorySize(int channels, int frames) {
        return CalculateMemorySizeInternal(channels, frames, nullptr);
    }

    int AudioBus::CalculateMemorySize(const AudioParameters& params) {
        return CalculateMemorySizeInternal(params.channel_count(),
                                           params.frames_per_buffer(),
                                           nullptr);
    }

    void AudioBus::Zero() {
        ZeroFrames(frames_);
    }

    void AudioBus::ZeroFrames(int frames) {
        ZeroFramesPartial(0, frames);
    }

    void AudioBus::ZeroFramesPartial(int start_frame, int frames) {
        CheckOverflow(start_frame, frames, frames_);

        if (frames <= 0)
            return;

        for (auto& data: channel_data_) {
            memset(data + start_frame, 0, frames * sizeof(*data));
        }
    }

    void AudioBus::CopyConvertFromInterleavedSourceToAudioBus(
            const float* source_buffer,
            int write_offset_in_frames,
            int num_frames_to_write,
            AudioBus* dest) {
        const int channels = dest->channels();
        for (int ch = 0; ch < channels; ch++) {
            float* channel_data = dest->channel(ch);
            for (int target_frame_index = write_offset_in_frames,
                         read_pos_in_source = ch;
                 target_frame_index < write_offset_in_frames + num_frames_to_write;
                 ++target_frame_index, read_pos_in_source += channels) {
                channel_data[target_frame_index] = source_buffer[read_pos_in_source];
            }
        }
    }

    void AudioBus::FromInterleavedPartial(const float* source_buffer,
                                          int write_offset_in_frames,
                                          int num_frames_to_write) {
        CheckOverflow(write_offset_in_frames,
                      num_frames_to_write,
                      frames_);
        CopyConvertFromInterleavedSourceToAudioBus(
                source_buffer,
                write_offset_in_frames,
                num_frames_to_write,
                this);
    }

    void AudioBus::CopyTo(AudioBus* dest) const {
        CopyPartialFramesTo(0, frames(), 0, dest);
    }

    void AudioBus::CopyPartialFramesTo(int source_start_frame,
                                       int frame_count,
                                       int dest_start_frame,
                                       AudioBus* dest) const {
        CHECK_EQ(channels(), dest->channels());
        CHECK_LE(source_start_frame + frame_count, frames());
        CHECK_LE(dest_start_frame + frame_count, dest->frames());

        // Since we don't know if the other AudioBus is wrapped or not (and we don't
        // want to care), just copy using the public channel() accessors.
        for (int i = 0; i < channels(); i++) {
            memcpy(dest->channel(i) + dest_start_frame,
                   channel(i) + source_start_frame,
                   sizeof(*channel(i)) * frame_count);
        }
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
