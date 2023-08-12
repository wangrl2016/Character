//
// Created by wangrl2016 on 2023/7/16.
//

#include "media/base/video_frame.h"
#include "media/base/video_frame_layout.h"

namespace media {
    std::shared_ptr<VideoFrame> VideoFrame::CreateFrame(VideoPixelFormat format,
                                                        base::TimeDelta timestamp) {

    }

    size_t VideoFrame::NumPlanes(VideoPixelFormat format) {
        return VideoFrameLayout::NumPlanes(format);
    }
}
