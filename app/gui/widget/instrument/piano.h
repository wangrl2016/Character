//
// Created by wangrl2016 on 2023/6/10.
//

#ifndef CHARACTER_PIANO_H
#define CHARACTER_PIANO_H

#include <array>
#include "core/midi/midi_event_processor.h"
#include "core/math/constant.h"

namespace app {
    class Piano {
    public:
        static const int kWhiteKeysPerOctave = 7;
        static const int kBlackKeysPerOctave = 5;
        // total 128
        static const int kNumWhiteKeys = 75;
        static const int kNumBlackKeys = 53;

        Piano();

        enum KeyType {
            kWhiteKey,
            kBlackKey,
        };

        // Turn a key on or off.
        // @param key   the key number to change
        // @param state the state to set the key to
        void SetKeyState(int key, bool state);

        [[nodiscard]] bool IsKeyPressed(int key) const {
            return pressed_keys_[key];
        }

        void HandleKeyPress(int key, int midi_velocity = -1);

        void HandleKeyRelease(int key);

        static bool IsWhiteKey(int key);

        static bool IsBlackKey(int key);

    private:
        static bool IsValidKey(int key) {
            return 0 <= key && key < kNumKeys;
        }

        // key is pressed or not?
        std::array<bool, kNumKeys> pressed_keys_ = {};
    };
}


#endif //CHARACTER_PIANO_H
