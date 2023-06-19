//
// Created by wangrl2016 on 2023/6/19.
//

#ifndef CHARACTER_TIME_POS_H
#define CHARACTER_TIME_POS_H

namespace ui {
    const int kDefaultTicksPerBar = 480;
    const int kDefaultStepsPerBar = 60;
    const int kDefaultBeatsPerBar = kDefaultTicksPerBar / kDefaultStepsPerBar;


    // Represents a time signature, in which the numerator is the number of beats
    // in a bar, while the denominator is the type of note representing a beat.
    // Example: 6/8 means beats in a bar with each beat having a during of one
    // 8th-note.
    class TimeSig {
    public:
        TimeSig(int num, int den) : num_(num), den_(den) {}

        [[nodiscard]] int numerator() const { return num_; }

        [[nodiscard]] int denominator() const { return den_; }

    private:
        int num_;
        int den_;
    };
}

#endif //CHARACTER_TIME_POS_H
