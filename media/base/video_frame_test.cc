//
// Created by wangrl2016 on 2023/8/6.
//

#include <gtest/gtest.h>
#include "base/time/time_delta.h"
#include "core/geometry/size.h"
#include "media/base/video_frame.h"

namespace media {
    TEST(VideoFrame, CreateFrame) {
        const int kWidth = 64;
        const int kHeight = 48;
        const base::TimeDelta kTimestamp = base::Microseconds(1337);

        // Create a YV12 Video frame.
        core::Size size(kWidth, kHeight);
        // std::shared_ptr<VideoFrame> frame = VideoFrame::CreateFrame();
    }
}
