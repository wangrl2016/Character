//
// Created by wangrl2016 on 2023/7/20.
//

#include <string>
#include "core/geometry/size.h"

namespace core {
    void Size::operator+=(const Size& size) {
        Enlarge(size.width(), size.height());
    }

    void Size::operator-=(const Size& size) {
        Enlarge(-size.width(), -size.height());
    }

    void Size::Enlarge(int grow_width, int grow_height) {
        SetSize(width() + grow_width,
                height() + grow_height);
    }

    std::string Size::ToString() const {
        return std::to_string(width()) + "x" + std::to_string(height());
    }

    Size ScaleToCeilSize(const Size& size, float x_scale, float y_scale) {
        if (x_scale == 1.0f && y_scale == 1.0f)
            return size;

        return {int(std::ceil(float(size.width()) * x_scale)),
                int(std::ceil(float(size.height()) * y_scale))};
    }

    Size ScaleToCeilSize(const Size& size, float scale) {
        if (scale == 1.0f)
            return size;
        return {int(std::ceil(float(size.width()) * scale)),
                int(std::ceil(float(size.height()) * scale))};
    }

    Size ScaleToFloorSize(const Size& size, float x_scale, float y_scale) {
        if (x_scale == 1.0f && y_scale == 1.0f)
            return size;

        return {int(std::floor(float(size.width()) * x_scale)),
                int(std::floor(float(size.height()) * y_scale))};
    }

    Size ScaleToFloorSize(const Size& size, float scale) {
        if (scale == 1.0f)
            return size;
        return {int(std::floor(float(size.width()) * scale)),
                int(std::floor(float(size.height()) * scale))};
    }

    Size ScaleToRoundSize(const Size& size, float x_scale, float y_scale) {
        if (x_scale == 1.0f && y_scale == 1.0f)
            return size;

        return {int(std::round(float(size.width()) * x_scale)),
                int(std::round(float(size.height()) * y_scale))};
    }

    Size ScaleToRoundSize(const Size& size, float scale) {
        if (scale == 1.0f)
            return size;
        return {int(std::round(float(size.width()) * scale)),
                int(std::round(float(size.height()) * scale))};
    }
}
