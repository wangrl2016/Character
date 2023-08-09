//
// Created by wangrl2016 on 2023/8/9.
//

#include "media/base/video_types.h"

namespace media {
    bool IsYuvPlanar(VideoPixelFormat format) {
        switch (format) {
            case kPixelFormatI420:
                return true;
            case kPixelFormatRGBA:
                return false;
            default:
                break;
        }
        return false;
    }

    bool IsRGB(VideoPixelFormat format) {
        switch (format) {
            case kPixelFormatRGBA:
                return true;
            case kPixelFormatI420:
                return false;
            default:
                break;
        }
        return false;
    }

    bool IsOpaque(VideoPixelFormat format) {
        return false;
    }

    size_t BitDepth(VideoPixelFormat format) {
        return 0;
    }
}
