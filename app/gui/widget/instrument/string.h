//
// Created by wr on 2023/7/2.
//

#ifndef CHARACTER_STRING_COMPONENT_H
#define CHARACTER_STRING_COMPONENT_H

#include <QPainterPath>

namespace app {
    // This component represents a horizontal vibrating musical string of fixed height
    // and variable length.
    class String {
    public:
        explicit String(int length);

        void StringPlucked(float pluck_position_relative);

        QPainterPath GenerateStringPath() const;

        void TimerCallback();

        void UpdateAmplitude();

        void UpdatePhase();
    private:
        int length_;
        float amplitude_ = 0.0f;
        const float max_amplitude_ = 12.0f;
        float phase_ = 0.0f;
    };
}

#endif //CHARACTER_STRING_COMPONENT_H
