//
// Created by wangrl2016 on 2023/8/2.
//

#ifndef CHARACTER_VIDEO_ASPECT_RATIO_H
#define CHARACTER_VIDEO_ASPECT_RATIO_H

#include "core/geometry/size.h"
#include "core/geometry/rect.h"

namespace media {
    class VideoAspectRatio {
    public:
        // Create a pixel aspect ratio (PAR). |width| and |height| describe the
        // shape of a pixel. For example, an anamorphic video has rectangular pixels
        // with a 2:1 PAR, that they are twice as wide as they are tall.
        //
        // Note that this is also called a sample aspect ratio (SAR), but SAR can also
        // mean storage aspect ratio (which is the coded size).
        static VideoAspectRatio PAR(int width, int height);

        // Create a display aspect ratio (DAR). |width| and |height| describe the
        // shape of the rendered picture. For example a 1920x1080 video with square
        // pixels has a 1920:1080 = 16:9 DAR.
        static VideoAspectRatio DAR(int width, int height);

        // A default-constructed VideoAspectRatio is !IsValid().
        VideoAspectRatio() = default;

        // An aspect ratio is invalid if it was default constructed, had non-positive
        // components, or exceeds implementation limits.
        [[nodiscard]] bool IsValid() const;

        // Computes the expected display size for a given visible size.
        // Returns visible_rect.size() if !IsValid().
        [[nodiscard]] core::Size GetNaturalSize(const core::Rect& visible_rect) const;

    private:
        enum class Type {
            kDisplay,
            kPixel,
        };

        VideoAspectRatio(Type type, int width, int height);

        Type type_ = Type::kDisplay;
        double aspect_ratio_ = 0.0;
    };
}

#endif //CHARACTER_VIDEO_ASPECT_RATIO_H
