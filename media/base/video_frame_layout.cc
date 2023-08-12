//
// Created by admin on 2023/8/10.
//

#include "media/base/video_frame_layout.h"

namespace media {
    std::vector<ColorPlaneLayout> PlanesFromStrides(
            const std::vector<int32_t>& strides) {
        std::vector<ColorPlaneLayout> planes(strides.size());
        for (size_t i = 0; i < strides.size(); i++) {
            planes[i].stride = strides[i];
        }
        return planes;
    }

    std::shared_ptr<VideoFrameLayout> VideoFrameLayout::Create(
            VideoPixelFormat format,
            const core::Size& coded_size) {
        return CreateWithStrides(format, coded_size,
                                 std::vector<int32_t>(NumPlanes(format), 0));
    }

    std::shared_ptr<VideoFrameLayout> VideoFrameLayout::CreateWithStrides(
            VideoPixelFormat format,
            const core::Size& coded_size,
            const std::vector<int32_t>& strides,
            size_t buffer_addr_align) {
        return CreateWithPlanes(format,
                                coded_size,
                                PlanesFromStrides(strides),
                                buffer_addr_align);
    }

    std::shared_ptr<VideoFrameLayout> VideoFrameLayout::CreateWithPlanes(
            VideoPixelFormat format,
            const core::Size& coded_size,
            std::vector<ColorPlaneLayout> planes,
            size_t buffer_addr_align) {
        return std::make_shared<VideoFrameLayout>(VideoFrameLayout(
                format,
                coded_size,
                std::move(planes),
                buffer_addr_align));
    }

    size_t VideoFrameLayout::NumPlanes(VideoPixelFormat format) {
        switch (format) {
            case kPixelFormatRGBA:
                return 1;
            case kPixelFormatI420:
                return 3;
            case kPixelFormatUnknown:
                return 0;
        }
        return 0;
    }

    bool VideoFrameLayout::operator==(const VideoFrameLayout& rhs) const {
        return format_ == rhs.format_ && coded_size_ == rhs.coded_size_ &&
               planes_ == rhs.planes_ && buffer_addr_align_ == rhs.buffer_addr_align_;
    }

    bool VideoFrameLayout::operator!=(const VideoFrameLayout& rhs) const {
        return !(*this == rhs);
    }

    VideoFrameLayout::VideoFrameLayout(VideoPixelFormat format,
                                       const core::Size& coded_size,
                                       std::vector<ColorPlaneLayout> planes,
                                       size_t buffer_addr_align)
            : format_(format),
              coded_size_(coded_size),
              planes_(std::move(planes)),
              buffer_addr_align_(buffer_addr_align) {

    }
}
