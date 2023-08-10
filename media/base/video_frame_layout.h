//
// Created by admin on 2023/8/10.
//

#ifndef CHARACTER_VIDEO_FRAME_LAYOUT_H
#define CHARACTER_VIDEO_FRAME_LAYOUT_H

#include "core/geometry/size.h"
#include "media/base/color_plane_layout.h"
#include "media/base/video_types.h"

namespace media {
    class VideoFrameLayout {
    public:
        // Default alignment for buffers.
        // Note: this value is dependent on what's used by ffmpeg, do not change
        // without inspecting av_frame_get_buffer() first.
        static constexpr size_t kBufferAddressAlignment = 32;

        // Factory functions.
        // |format| and |coded_size| must always be specified.
        // |planes| info is also optional but useful to represent the layout of a
        // video frame buffer correctly. When omitted, its information is all set
        // to zero, so clients should be wary not to use this information.
        // |buffer_addr_align| can be specified to request a specific buffer memory
        // alignment.
        static std::shared_ptr<VideoFrameLayout> Create(VideoPixelFormat format,
                                                        const core::Size& coded_size);

        static std::shared_ptr<VideoFrameLayout> CreateWithStrides(
                VideoPixelFormat format,
                const core::Size& coded_size,
                std::vector<int32_t> strides,
                size_t buffer_addr_align = kBufferAddressAlignment);

        VideoFrameLayout() = delete;

        VideoFrameLayout(const VideoFrameLayout&);

        VideoFrameLayout(VideoFrameLayout&&);

        VideoFrameLayout& operator=(const VideoFrameLayout&);

        ~VideoFrameLayout();

    private:
        VideoFrameLayout(VideoPixelFormat format,
                         const core::Size coded_size,
                         std::vector<ColorPlaneLayout> planes,
                         size_t buffer_addr_align);

        VideoPixelFormat format_;

        // Width and height of the video frame in pixels. This must include pixel
        // data for the whole image; i.e. for YUV formats with sub-sampled chroma
        // planes, in the case that the visible portion of the image does not line up
        // on a sample boundary, |coded_size_| must be rounded up appropriately and
        // the pixel data provided for the odd pixels.
        core::Size coded_size_;

        // Layout property for each color planes, e.g. stride and buffer offset.
        std::vector<ColorPlaneLayout> planes_;

        // Memory address alignment of the buffers. This is only relevant when
        // allocating physical memory for the buffer.
        size_t buffer_addr_align_;

    };
}

#endif //CHARACTER_VIDEO_FRAME_LAYOUT_H
