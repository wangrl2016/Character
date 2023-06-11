//
// Created by wangrl2016 on 2023/6/3.
//

#ifndef CHARACTER_AUDIO_BUS_H
#define CHARACTER_AUDIO_BUS_H

#include <memory>
#include "media/base/audio_parameters.h"
#include "base/memory/aligned_memory.h"

namespace media {
    class AudioBus {
    public:
        // Guaranteed alignment of each channel's data; use 16-byte alignment for
        // easy SSE optimizations.
        enum {
            kChannelAlignment = 16
        };

        void CheckOverflow(int start_frame, int frames, int total_frames);

        // Creates a new AudioBus and allocates |channels| of length |frames|. Uses
        // channels() and frames_per_buffer() from AudioParameters if given.
        static std::unique_ptr<AudioBus> Create(int channels, int frames);

        static std::unique_ptr<AudioBus> Create(const AudioParameters& params);

        // Creates a new AudioBus from an existing channel vector. Does not transfer
        // ownership of |channel_data| to AudioBus; i.e., |channel_data| must outlive
        // the returned AudioBus. Each channel must be aligned by kChannelAlignment.
        static std::unique_ptr<AudioBus> WrapVector(
                int frames,
                const std::vector<float*>& channel_data);

        // Creates a new AudioBus by wrapping an existing block of memory. Block must
        // be at least CalculateMemorySize() bytes in size. |data| must outlive the
        // returned AudioBus. |data| must be aligned by kChannelAlignment.
        static std::unique_ptr<AudioBus> WrapMemory(int channels,
                                                    int frames,
                                                    void* data);

        static std::unique_ptr<AudioBus> WrapMemory(const AudioParameters& params,
                                                    void* data);

        // Based on the given number of channels and frames, calculates the minimum
        // required size in bytes of a contiguous block of memory to be passed to
        // AudioBus for storage of the audio data.
        // Uses channel_count() and frames_per_buffer() from AudioParameters if given.
        static int CalculateMemorySize(int channels, int frames);

        static int CalculateMemorySize(const AudioParameters& params);

        // Returns a raw pointer to the requested channel. Pointer is guaranteed to have
        // a 16-byte alignment. Warning: Do not rely on have sane (i.e. not
        // inf, nan, or between [-1.0, 1.0]) values in the channel data.
        float* channel(int channel) { return channel_data_[channel]; }

        const float* channel(int channel) const { return channel_data_[channel]; }

        // Returns the number of channels.
        int channels() const { return static_cast<int>(channel_data_.size()); }

        // Return the number of frames.
        int frames() const { return frames_; }

        // Helper method for zeroing out all channels of audio data.
        void Zero();

        void ZeroFrames(int frames);

        void ZeroFramesPartial(int start_frame, int frames);

        // Check if all frames are zero.
        bool AreFramesZero() const;

        // Scale internal channel values by |volume| >= 0.  If an invalid value
        // is provided, no adjustment is done.
        void Scale(float volume);

        // Swaps channels identified by |a| and |b|.  The caller needs to make sure
        // the channels are valid.
        void SwapChannels(int a, int b);

        static void CopyConvertFromInterleavedSourceToAudioBus(
                const float* source_buffer,
                int write_offset_in_frames,
                int num_frames_to_write,
                AudioBus* dest);

        void FromInterleavedPartial(
                const float* source_buffer,
                int write_offset_in_frames,
                int num_frames_to_write);

        // Helper method for copying channel data from one AudioBus to another. Both
        // AudioBus object must have the same frames() and channels().
        void CopyTo(AudioBus* dest) const;

        // Helper method to copy frames from one AudioBus to another. Both AudioBus
        // objects must have the same number of channels(). |source_start_frame| is
        // the starting offset. |dest_start_frame| is the starting offset in |dest|.
        // |frame_count| is the number of frames to copy.
        void CopyPartialFramesTo(int source_start_frame,
                                 int frame_count,
                                 int dest_start_frame,
                                 AudioBus* dest) const;

    protected:
        AudioBus(int channels, int frames);

        AudioBus(int channels, int frames, float* data);

        AudioBus(int frames, const std::vector<float*>& channel_data);

    private:
        // Helper method for building |channel_data_| from a block of memory.
        // |data| must be at least CalculateMemorySize(...) bytes in size.
        void BuildChannelData(int channels, int aligned_frames, float* data);

        // Contiguous block of channel memory.
        std::unique_ptr<float, base::AlignedFreeDeleter> data_;

        // One float pointer per channel pointing to a contiguous block of memory for
        // that channel. If the memory is owned by this instance, this will
        // point to the memory in |data_|. Otherwise, it may point to memory provied
        // by the client.
        std::vector<float*> channel_data_;
        int frames_;
    };
}

#endif //CHARACTER_AUDIO_BUS_H
