//
// Created by wangrl2016 on 2023/6/4.
//

#ifndef CHARACTER_TIME_DELTA_H
#define CHARACTER_TIME_DELTA_H

#include <cstdint>
#include <limits>

namespace base {
    class TimeDelta;

    static constexpr int64_t kHoursPerDay = 24;
    static constexpr int64_t kSecondsPerMinute = 60;
    static constexpr int64_t kMinutesPerHour = 60;
    static constexpr int64_t kSecondsPerHour = kSecondsPerMinute * kMinutesPerHour;
    static constexpr int64_t kMillisecondsPerSecond = 1000;
    static constexpr int64_t kMillisecondsPerDay =
            kMillisecondsPerSecond * kSecondsPerHour * kHoursPerDay;
    static constexpr int64_t kMicrosecondsPerMillisecond = 1000;
    static constexpr int64_t kMicrosecondsPerSecond =
            kMicrosecondsPerMillisecond * kMillisecondsPerSecond;
    static constexpr int64_t kMicrosecondsPerMinute =
            kMicrosecondsPerSecond * kSecondsPerMinute;


    class TimeDelta {
    public:
        constexpr TimeDelta() = default;

        constexpr explicit TimeDelta(int64_t delta_us) : delta_(delta_us) {}

        static constexpr TimeDelta Max();

        static constexpr TimeDelta Min();

        [[nodiscard]] constexpr bool is_max() const { return *this == Max(); }

        [[nodiscard]] constexpr bool is_min() const { return *this == Min(); }

        [[nodiscard]] constexpr bool is_inf() const { return is_min() || is_max(); }

        [[nodiscard]] constexpr int InMinutes() const;

        [[nodiscard]] constexpr double InSecondsF() const;

        [[nodiscard]] constexpr int64_t InSeconds() const;

        [[nodiscard]] double InMillisecondsF() const;

        [[nodiscard]] int64_t InMilliseconds() const;

        [[nodiscard]] int64_t InMillisecondsRoundedUp() const;

        constexpr bool operator==(TimeDelta other) const {
            return delta_ == other.delta_;
        }

    private:
        int64_t delta_ = 0;
    };

    constexpr TimeDelta TimeDelta::Max() {
        return TimeDelta(std::numeric_limits<int64_t>::max());
    }

    constexpr TimeDelta TimeDelta::Min() {
        return TimeDelta(std::numeric_limits<int64_t>::min());
    }

    constexpr int TimeDelta::InMinutes() const {
        return int(delta_ / kMicrosecondsPerMinute);
    }

    constexpr double TimeDelta::InSecondsF() const {
        if (!is_inf())
            return static_cast<double>(delta_) / kMicrosecondsPerSecond;
        return (delta_ < 0) ? -std::numeric_limits<double>::infinity()
                            : std::numeric_limits<double>::infinity();
    }

    constexpr int64_t TimeDelta::InSeconds() const {
        return is_inf() ? delta_ : (delta_ / kMicrosecondsPerSecond);
    }

    template<typename T>
    constexpr TimeDelta Microseconds(T n) {
        return TimeDelta(n);
    }
}

#endif //CHARACTER_TIME_DELTA_H
