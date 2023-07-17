//
// Created by wangrl2016 on 2023/7/17.
//

#include <gtest/gtest.h>
#include "media/base/video_frame.h"

namespace media {
    class FFmpegVideoDecoderTest : public testing::Test {
    public:
        typedef std::vector<std::shared_ptr<DecoderBuffer>> InputBuffers;
        typedef std::vector<std::shared_ptr<VideoFrame>> OutputFrames;



    };
}
