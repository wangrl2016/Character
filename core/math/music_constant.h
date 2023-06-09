//
// Created by wangrl2016 on 2023/6/11.
//

#ifndef CHARACTER_MUSIC_CONSTANT_H
#define CHARACTER_MUSIC_CONSTANT_H

#define _USE_MATH_DEFINES
#include <cmath>

enum Keys {
    kKeyC = 0,
    kKeyCIS = 1, kKeyDES = 1,
    kKeyD = 2,
    kKeyDIS = 3, kKeyES = 3,
    kKeyE = 4, kKeyFES = 4,
    kKeyF = 5,
    kKeyFIS = 6, kKeyGES = 6,
    kKeyG = 7,
    kKeyGIS = 8, kKeyAS = 8,
    kKeyA = 9,
    kKeyAIS = 10, kKeyB = 10,
    kKeyH = 11,
};

enum Octaves {
    kOctaveM1,  // MIDI standard starts at C-1
    kOctave0,
    kOctave1,
    kOctave2,
    kOctave3,
    kOctave4,
    kDefaultOctave = kOctave4,
    kOctave5,
    kOctave6,
    kOctave7,
    kOctave8,
    kOctave9,
    kNumOctaves,
};

constexpr int kFirstOctave = -1;
constexpr int kKeysPerOctave = 12;
constexpr int kDefaultKey = kDefaultOctave * kKeysPerOctave + kKeyA;
// Number of physical keys, limited to MIDI range (valid for both MIDI 1.0 and 2.0)
constexpr int kNumKeys = 128;

constexpr int kDefaultMiddleKey = kOctave4 * kKeysPerOctave + kKeyC;    // 60
constexpr int kDefaultBaseKey = kOctave4 * kKeysPerOctave + kKeyA;      // 69
constexpr float kDefaultBaseFreq = 440.0f;

#endif //CHARACTER_MUSIC_CONSTANT_H
