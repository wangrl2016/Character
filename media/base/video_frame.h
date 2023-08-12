//
// Created by wangrl2016 on 2023/7/16.
//

#ifndef CHARACTER_VIDEO_FRAME_H
#define CHARACTER_VIDEO_FRAME_H

#include <cstdio>
#include <cstdint>
#include <memory>
#include "base/time/time_delta.h"
#include "media/base/video_types.h"

namespace media {
    class VideoFrame {
    public:
        static constexpr size_t kFrameSizeAlignment = 16;
        static constexpr size_t kFrameSizePadding = 16;

        enum {
            kMaxPlanes = 4,
            kYPlane = 0,
            kARGBPlane = kYPlane,
            kUPlane = 1,
            kUVPlane = kUPlane,
            kVPlane = 2,
            kAPlaneTriPlanar = kVPlane,
            kAPlane = 3,
        };

        VideoFrame() = delete;

        VideoFrame(const VideoFrame&) = delete;

        VideoFrame& operator=(const VideoFrame&) = delete;

        static std::shared_ptr<VideoFrame> CreateFrame(VideoPixelFormat format,
                                                       base::TimeDelta timestamp);

        static size_t NumPlanes(VideoPixelFormat format);


        // Array of data pointers to each plane.
        const uint8_t* data_[kMaxPlanes];

        base::TimeDelta timestamp_;
    };
}

#endif //CHARACTER_VIDEO_FRAME_H
