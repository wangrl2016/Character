//
// Created by wangrl2016 on 2023/8/1.
//

#include "core/geometry/point.h"

namespace core {
    std::string Point::ToString() const {
        return std::to_string(x()) + "," + std::to_string(y());
    }
}
