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

        [[nodiscard]] constexpr int width() const { return width_; }

        [[nodiscard]] constexpr int height() const { return height_; }

        void set_width(int width) { width_ = std::max(0, width); }

        void set_height(int height) { height_ = std::max(0, height); }

        [[nodiscard]] int GetArea() const { return width_ * height_; }

        void SetSize(int width, int height) {
            set_width(width);
            set_height(height);
        }

        void Enlarge(int grow_width, int grow_height);

        [[nodiscard]] bool IsEmpty() const { return !width() || !height(); }

        [[nodiscard]] bool IsZero() const { return !width() && !height(); }

        void Transpose() {
            std::swap(width_, height_);
        }

        [[nodiscard]] std::string ToString() const;

    private:
        int width_;
        int height_;
    };

    inline bool operator==(const Size& lhs, const Size& rhs) {
        return lhs.width() == rhs.width() && lhs.height() == rhs.height();
    }

    inline bool operator!=(const Size& lhs, const Size& rhs) {
        return !(lhs == rhs);
    }

    inline Size operator+(Size lhs, const Size& rhs) {
        lhs += rhs;
        return lhs;
    }

    inline Size operator-(Size lhs, const Size& rhs) {
        lhs -= rhs;
        return lhs;
    }

    // Helper methods to scale a Size to a new Size.
    Size ScaleToCeilSize(const Size& size, float x_scale, float y_scale);

    Size ScaleToCeilSize(const Size& size, float scale);

    Size ScaleToFloorSize(const Size& size, float x_scale, float y_scale);

    Size ScaleToFloorSize(const Size& size, float scale);

    Size ScaleToRoundSize(const Size& size, float x_scale, float y_scale);

    Size ScaleToRoundSize(const Size& size, float scale);
}

#endif //CHARACTER_SIZE_H
