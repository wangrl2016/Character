//
// Created by wangrl2016 on 2023/8/1.
//

#ifndef CHARACTER_RECT_H
#define CHARACTER_RECT_H

#include "core/geometry/point.h"
#include "core/geometry/size.h"

namespace core {
    class Rect {
    public:
        constexpr Rect() = default;

        constexpr Rect(int width, int height) : size_(width, height) {}

        constexpr Rect(int x, int y, int width, int height) :
                origin_(x, y),
                size_(width, height) {}

        constexpr explicit Rect(const Size& size) : size_(size) {}

        constexpr Rect(const Point& origin, const Size& size) :
                origin_(origin),
                size_(size.width(), size.height()) {}

        [[nodiscard]] constexpr int width() const { return size_.width(); }

        void set_width(int width) { size_.set_width( width); }

        [[nodiscard]] constexpr int height() const { return size_.height(); }

        void set_height(int height) { size_.set_height(height); }

        [[nodiscard]] constexpr const Size& size() const { return size_; }

        // Returns true if the area of the rectangle is zero.
        [[nodiscard]] bool IsEmpty() const { return size_.IsEmpty(); }

    private:
        Point origin_;
        Size size_;
    };
}

#endif //CHARACTER_RECT_H
