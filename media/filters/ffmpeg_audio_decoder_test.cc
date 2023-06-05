//
// Created by wangrl2016 on 2023/6/5.
//

#include <gtest/gtest.h>

namespace media {
    class FFmpegAudioDecoderTest : public testing::Test {
    public:
        void Initialize(const char* filename) {

        }


    };

    TEST_F(FFmpegAudioDecoderTest, WithoutOpen) {
        Initialize("bear.ogv");
    }
}