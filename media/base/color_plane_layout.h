//
// Created by wangrl2016 on 2023/8/10.
//

#ifndef CHARACTER_COLOR_PLANE_LAYOUT_H
#define CHARACTER_COLOR_PLANE_LAYOUT_H

#include <cstdio>
#include <ostream>

namespace media {
    // Encapsulates a color plane's memory layout: (stride, offset, size)
    // stride: in bytes of a plane. Note that stride can be negative if the image
    //         layout is bottom-up.
    // offset: in bytes of a plane, which stands for the offset of a start point of
    //         color plane from a buffer FD.
    // size:   in bytes of a plane. This |size| bytes data must contain all the data
    //         a decoder will access (e.g. visible area and padding).
    struct ColorPlaneLayout {
        ColorPlaneLayout();

        ColorPlaneLayout(int32_t stride, size_t offset, size_t size);

        ~ColorPlaneLayout();

        bool operator==(const ColorPlaneLayout& rhs) const;

        bool operator!=(const ColorPlaneLayout& rhs) const;

        int32_t stride = 0;
        size_t offset = 0;
        size_t size = 0;
    };

    // Outputs ColorPlaneLayout to stream.
    std::ostream& operator<<(std::ostream& ostream,
                             const ColorPlaneLayout& plane);
}

#endif //CHARACTER_COLOR_PLANE_LAYOUT_H
