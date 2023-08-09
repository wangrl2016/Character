//
// Created by wangrl2016 on 2023/8/9.
//

#ifndef CHARACTER_VIDEO_TYPES_H
#define CHARACTER_VIDEO_TYPES_H

namespace media {
    // When a VideoFrame is backed by native textures, VideoPixelFormat describes
    // how those textures should be sampled and combined to produce the final
    // pixels.
    enum VideoPixelFormat {
        kPixelFormatUnknown = 0,        // Unknown or unspecified format value
        kPixelFormatI420 = 1,           // 12bpp YUV planar 1x1 Y, 2x2 UV samples, a.k.a. YU12
        kPixelFormatRGBA = 2,           // 32bpp RGBA (byte-order), 1 plane
    };

    // Returns ture if |format| is an RGB format.
    bool isRGB(VideoPixelFormat format);


    bool IsOpaque(VideoPixelFormat format);
}


#endif //CHARACTER_VIDEO_TYPES_H
