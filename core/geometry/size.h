//
// Created by wangrl2016 on 2023/7/20.
//

#ifndef CHARACTER_SIZE_H
#define CHARACTER_SIZE_H

#include <algorithm>

namespace core {
    // A size has width and height values.
    class Size {
    public:
        constexpr Size() : width_(0), height_(0) {}

        constexpr Size(int width, int height) :
                width_(std::max(0, width)), height_(std::max(0, height)) {}

        void operator+=(const Size& size);

        void operator-=(const Size& size);

        constexpr int width() const { return width_; }

        constexpr int height() const { return height_; }

        void set_width(int width) { width_ = std::max(0, width); }

        void set_height(int height) { height_ = std::max(0, height); }

        [[nodiscard]] int GetArea() const { return width_ * height_; }

    private:
        int width_;
        int height_;
    };
}

#endif //CHARACTER_SIZE_H
