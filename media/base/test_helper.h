//
// Created by wangrl2016 on 2023/8/2.
//

#ifndef CHARACTER_TEST_HELPER_H
#define CHARACTER_TEST_HELPER_H

#include "media/base/video_decoder_config.h"

namespace media {
    class TestVideoConfig {
    public:
        static VideoDecoderConfig Invalid();

        static VideoDecoderConfig Normal(AVCodecID codec = AV_CODEC_ID_VP8);
    };
}

#endif //CHARACTER_TEST_HELPER_H
