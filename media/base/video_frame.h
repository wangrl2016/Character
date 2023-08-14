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
#include "video_frame_layout.h"

namespace media {
    class VideoFrame {
    public:
        static constexpr size_t kFrameSizeAlignment = 16;
        static constexpr size_t kFrameSizePadding = 16;

        static constexpr size_t kFrameAddressAlignment =
                VideoFrameLayout::kBufferAddressAlignment;

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

        static bool IsValidSize(const core::Size& coded_size,
                                const core::Size& visible_rect,
                                const core::Size& natural_size);

        static bool IsValidCodedSize(const core::Size& size);

        static std::shared_ptr<VideoFrame> CreateFrame(VideoPixelFormat format,
                                                       base::TimeDelta timestamp);

        // Allocates YV12 frame based on |size|, and sets it data to the YUV.
        static std::shared_ptr<VideoFrame> CreateColorFrame(const core::Size& size,
                                                            uint8_t y,
                                                            uint8_t u,
                                                            uint8_t v,
                                                            base::TimeDelta timestamp);

        static size_t NumPlanes(VideoPixelFormat format);

        static size_t AllocationSize(VideoPixelFormat format,
                                     const core::Size& coded_size);

    private:

        // Array of data pointers to each plane.
        const uint8_t* data_[kMaxPlanes];

        base::TimeDelta timestamp_;
    };
}

#endif //CHARACTER_VIDEO_FRAME_H
