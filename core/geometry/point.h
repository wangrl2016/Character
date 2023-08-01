//
// Created by wangrl2016 on 2023/8/1.
//

#ifndef CHARACTER_POINT_H
#define CHARACTER_POINT_H

#include <algorithm>
#include <string>

namespace core {
    class Point {
    public:
        constexpr Point() : x_(0), y_(0) {}

        constexpr Point(int x, int y) : x_(x), y_(y) {}

        [[nodiscard]] constexpr int x() const { return x_; }

        [[nodiscard]] constexpr int y() const { return y_; }

        void set_x(int x) { x_ = x; }

        void set_y(int y) { y_ = y; }

        void SetPoint(int x, int y) {
            x_ = x;
            y_ = y;
        }

        void Offset(int delta_x, int delta_y) {
            x_ = x_ + delta_x;
            y_ = y_ + delta_y;
        }

        [[nodiscard]] bool IsOrigin() const { return x_ == 0 && y_ == 0; }

        void Transpose() { std::swap(x_, y_); }

        bool operator<(const Point& rhs) const {
            return std::tie(y_, x_) < std::tie(rhs.y_, rhs.x_);
        }

        // Returns a string representation of point.
        [[nodiscard]] std::string ToString() const;

    private:
        int x_;
        int y_;
    };
}

#endif //CHARACTER_POINT_H
