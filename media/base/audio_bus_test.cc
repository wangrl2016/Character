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

        ~AudioBusTest() override {

        }

    protected:
        std::vector<float*> data_;
    };
}
