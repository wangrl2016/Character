//
// Created by wangrl2016 on 2023/6/10.
//

#include "app/gui/widget/instrument/piano.h"
#include "module/audio_graph/audio_bridge.h"

namespace app {
    static const auto kKeyOrder = std::array {
        // C                CIS                 D                   DIS
        Piano::kWhiteKey,   Piano::kBlackKey,   Piano::kWhiteKey,   Piano::kBlackKey,
        // E                F                   FIS                 G
        Piano::kWhiteKey,   Piano::kWhiteKey,   Piano::kBlackKey,   Piano::kWhiteKey,
        // GIS              A                   AIS                 B
        Piano::kBlackKey,   Piano::kWhiteKey,   Piano::kBlackKey,   Piano::kWhiteKey,
    };

    Piano::Piano() = default;

    void Piano::SetKeyState(int key, bool state) {
        if (IsValidKey(key)) {
            pressed_keys_[uint64_t(key)] = state;
            if (state) {
                audio_graph::AudioBridge::TapDown(key);
            } else {
                audio_graph::AudioBridge::TapUp(key);
            }
            // emit DataChanged();
        }
    }

    // Handle a note being pressed on our keyboard display
    //
    // @param key the key being pressed
    void Piano::HandleKeyPress(int key, int midi_velocity) {

    }

    void Piano::HandleKeyRelease(int key) {

    }

    bool Piano::IsWhiteKey(int key) {
        return !IsBlackKey(key);
    }

    bool Piano::IsBlackKey(int key) {
        auto key_code = uint64_t(key % kKeysPerOctave);
        return kKeyOrder[key_code] == Piano::kBlackKey;
    }
}
