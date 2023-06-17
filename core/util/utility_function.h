//
// Created by wangrl2016 on 2023/6/13.
//

#ifndef CHARACTER_UTILITY_FUNCTION_H
#define CHARACTER_UTILITY_FUNCTION_H

#include "core/math/constant.h"

namespace core {
    // Converts linear amplitude [0, 1.0] to dBFS [-100, 0] scale.
    //
    // @param amp linear amplitude, where 1.0 = 0dBFS
    // @return amplitude in dBFS
    static inline float Amp2dBFS(float amp) {
        return float(20.0 * (amp > 0.00001 ? log(amp) : -5.0));
    }

    // Converts dBFS [-100, 0] scale to linear amplitude [0, 1.0].
    // @param dBFS the dBFS value convert, must be a real number.
    // @return linear amplitude
    static inline float dBFS2Amp(float dBFS) {
        return float(std::pow(10.0, dBFS / 20.0));
    }

    static inline float Pitch2Frequency(int pitch) {
        return std::powf(2.0f, float(pitch - kDefaultBaseKey) / kKeysPerOctave) * kDefaultBaseFreq;
    }
}

#endif //CHARACTER_UTILITY_FUNCTION_H
