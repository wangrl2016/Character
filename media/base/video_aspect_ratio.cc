//
// Created by wangrl216 on 2023/8/2.
//

#include "media/base/video_aspect_ratio.h"

namespace media {
    VideoAspectRatio VideoAspectRatio::PAR(int width, int height) {
        return {Type::kPixel, width, height};
    }

    VideoAspectRatio VideoAspectRatio::DAR(int width, int height) {
        return {Type::kDisplay, width, height};
    }

    VideoAspectRatio::VideoAspectRatio(Type type, int width, int height) {
        type_ = type;
        aspect_ratio_ = height ? static_cast<double>(width) / height : 0.0;
    }

    bool VideoAspectRatio::IsValid() const {
        return std::isfinite(aspect_ratio_) && aspect_ratio_ > 0.0;
    }

    core::Size VideoAspectRatio::GetNaturalSize(const core::Rect& visible_rect) const {
        if (!IsValid() || visible_rect.IsEmpty())
            return visible_rect.size();

        // Cast up front to simplify expressions.
        // WARNING: Some aspect ratios can result in sizes that exceed INT_MAX.
        double w = visible_rect.width();
        double h = visible_rect.height();

        switch (type_) {
            case Type::kDisplay:
                if (aspect_ratio_ >= w / h) {
                    // Display aspect is wider, grow width.
                    w = h * aspect_ratio_;
                } else {
                    // Display aspect is narrower, grow height.
                    h = w / aspect_ratio_;
                }
                break;

            case Type::kPixel:
                if (aspect_ratio_ >= 1.0) {
                    // Wide pixels, grow width.
                    w = w * aspect_ratio_;
                } else {
                    // Narrow pixels, grow height.
                    h = h / aspect_ratio_;
                }
                break;
        }

        // A valid natural size is positive (at least 1 after truncation) and fits in
        // an int. Underflow should only be possible if the input sizes were already
        // invalid, because the mutations above only increase the size.
        w = std::round(w);
        h = std::round(h);

        if (w < 1.0 || w > std::numeric_limits<int>::max() || h < 1.0 ||
            h > std::numeric_limits<int>::max()) {
            return visible_rect.size();
        }

        return {static_cast<int>(w), static_cast<int>(h)};
    }
}
