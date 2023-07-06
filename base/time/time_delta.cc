//
// Created by wangrl2016 on 2023/6/4.
//

#include "base/time/time_delta.h"

namespace base {
    double TimeDelta::InMillisecondsF() const {
        if (!is_inf())
            return static_cast<double>(delta_) / kMicrosecondsPerMillisecond;
        return (delta_ < 0) ? -std::numeric_limits<double>::infinity()
                            : std::numeric_limits<double>::infinity();
    }

    int64_t TimeDelta::InMilliseconds() const {
        if (!is_inf())
            return delta_ / kMicrosecondsPerMillisecond;
        return (delta_ < 0) ? std::numeric_limits<int64_t>::min()
                            : std::numeric_limits<int64_t>::max();
    }

    int64_t TimeDelta::InMillisecondsRoundedUp() const {
        if (!is_inf()) {
            const int64_t result = delta_ / kMicrosecondsPerMillisecond;
            // convert |result| from truncating to ceiling.
            return (delta_ > result * kMicrosecondsPerMillisecond) ? (result + 1)
                                                                   : result;
        }
        return delta_;
    }
}
