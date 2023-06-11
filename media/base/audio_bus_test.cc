//
// Created by wangrl2016 on 2023/6/7.
//

extern "C" {
#include <libavutil/channel_layout.h>
}

#include <gtest/gtest.h>
#include "media/base/audio_bus.h"

namespace media {
    static const int kChannels = 6;
    static constexpr int kChannelLayout = AV_CH_LAYOUT_5POINT1;
    // Use a buffer size which is intentionally not a multiple of kChannelAlignment.
    static const int kFrameCount = AudioBus::kChannelAlignment * 32 - 1;
    static const int kSampleRate = 48000;

    class AudioBusTest : public testing::Test {
    public:
        AudioBusTest() = default;

        AudioBusTest(const AudioBusTest&) = delete;

        AudioBusTest& operator=(const AudioBusTest&) = delete;

        ~AudioBusTest() = default;

        void VerifyChannelAndFrameCount(AudioBus* bus) {
            EXPECT_EQ(kChannels, bus->channels());
            EXPECT_EQ(kFrameCount, bus->frames());
        }

        void VerifyArrayIsFilledWithValue(const float data[], int size, float value) {
            for (int i = 0; i < size; i++)
                ASSERT_FLOAT_EQ(value, data[i]) << " i = " << i;
        }

        void VerifyAreEqualWithEpsilon(const AudioBus* result,
                                       const AudioBus* expected,
                                       float epsilon) {
            ASSERT_EQ(expected->channels(), result->channels());
            ASSERT_EQ(expected->frames(), result->frames());

            for (int ch = 0; ch < result->channels(); ch++) {
                for (int i = 0; i < result->frames(); i++) {
                    if (epsilon == 0) {
                        ASSERT_FLOAT_EQ(expected->channel(ch)[i], result->channel(ch)[i]);
                    } else {
                        ASSERT_NEAR(expected->channel(ch)[i], result->channel(ch)[i], epsilon);
                    }
                }
            }
        }

        // Verify values for each channel in |result| against |expected|.
        void VerifyAreEqual(const AudioBus* result, const AudioBus* expected) {
            VerifyAreEqualWithEpsilon(result, expected, 0);
        }

        // Read and write to the full extent of the allocated channel data. Also test
        // the Zero() method and verify it does as advertised. Also test data if data
        // is 16-byte aligned as advertised (see kChannelAlignment in audio_bus.h).
        void VerifyReadWriteAndAlignment(AudioBus* bus) {
            for (int i = 0; i < bus->channels(); i++) {
                // Verify that the address returned by channel(i) is a multiple of
                // AudioBus::kChannelAlignment.
                ASSERT_EQ(0U, reinterpret_cast<uintptr_t>(
                        bus->channel(i)) & (AudioBus::kChannelAlignment - 1));

                // Write into the channel buffer.
                std::fill(bus->channel(i), bus->channel(i) + bus->frames(), i);
            }

            for (int i = 0; i < bus->channels(); i++) {
                VerifyArrayIsFilledWithValue(bus->channel(i), bus->frames(), i);
            }

            bus->Zero();

            for (int i = 0; i < bus->channels(); i++) {
                VerifyArrayIsFilledWithValue(bus->channel(i), bus->frames(), 0);
            }
        }

        // Verify copying to and from |bus1| and |bus2|.
        void CopyTest(AudioBus* bus1, AudioBus* bus2) {
            // Fill |bus1| with dummy data.
            for (int i = 0; i < bus1->channels(); i++)
                std::fill(bus1->channel(i), bus1->channel(i) + bus1->frames(), i);

            // Verify copy from |bus1| to |bus2|.
            bus2->Zero();
            bus1->CopyTo(bus2);
            VerifyAreEqual(bus1, bus2);

            // Verify copy from |bus2| to |bus1|.
            bus1->Zero();
            bus2->CopyTo(bus1);
            VerifyAreEqual(bus2, bus1);
        }

    protected:
        std::vector<float*> data_;
    };

    // Verify basic Create(...) method works as advertised.
    TEST_F(AudioBusTest, Create) {
        std::unique_ptr<AudioBus> bus = AudioBus::Create(kChannels, kFrameCount);
        VerifyChannelAndFrameCount(bus.get());
        VerifyReadWriteAndAlignment(bus.get());
    }

    // Verify Create(...) using AudioParameters works as advertised.
    TEST_F(AudioBusTest, CreateUsingAudioParameters) {
        std::unique_ptr<AudioBus> bus = AudioBus::Create(
                AudioParameters(kSampleRate,
                                av_get_channel_layout_nb_channels(kChannelLayout),
                                AV_SAMPLE_FMT_FLTP,
                                kFrameCount));
        VerifyChannelAndFrameCount(bus.get());
        VerifyReadWriteAndAlignment(bus.get());
    }

    // Verify an AudioBus created via wrapping a vector works as advertised.
    TEST_F(AudioBusTest, WrapVector) {
        data_.reserve(kChannels);
        for (int i = 0; i < kChannels; i++) {
            data_.push_back(static_cast<float*>(base::AlignedAlloc(
                    sizeof(*data_[i]) * kFrameCount, AudioBus::kChannelAlignment)));
        }

        std::unique_ptr<AudioBus> bus = AudioBus::WrapVector(kFrameCount, data_);
        VerifyChannelAndFrameCount(bus.get());
        VerifyReadWriteAndAlignment(bus.get());
    }

    // Verify an AudioBus created via wrapping a memory block works as advertised.
    TEST_F(AudioBusTest, WrapMemory) {
        AudioParameters params(
                kSampleRate,
                av_get_channel_layout_nb_channels(kChannelLayout),
                AV_SAMPLE_FMT_FLTP,
                kFrameCount);

        int data_size = AudioBus::CalculateMemorySize(params);
        std::unique_ptr<float, base::AlignedFreeDeleter> data(static_cast<float*>(
                base::AlignedAlloc(data_size, AudioBus::kChannelAlignment)));

        // Fill the memory with a test value we can check for after wrapping.
        static const float kTestValue = 3;
        std::fill(data.get(), data.get() + data_size / sizeof(*data), kTestValue);
    }
}
