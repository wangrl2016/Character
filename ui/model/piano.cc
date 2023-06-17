//
// Created by wangrl2016 on 2023/6/10.
//

#include <array>
#include "ui/model/piano.h"
#include "module/audio_graph/audio_bridge.h"

namespace ui {
    static const auto kKeyOrder = std::array {
        // C                CIS                 D                   DIS
        Piano::kWhiteKey,   Piano::kBlackKey,   Piano::kWhiteKey,   Piano::kBlackKey,
        // E                F                   FIS                 G
        Piano::kWhiteKey,   Piano::kWhiteKey,   Piano::kBlackKey,   Piano::kWhiteKey,
        // GIS              A                   AIS                 B
        Piano::kBlackKey,   Piano::kWhiteKey,   Piano::kBlackKey,   Piano::kWhiteKey,
    };

    Piano::Piano(InstrumentTrack* track) :
            Model(nullptr) {

    }

    void Piano::SetKeyState(int key, bool state) {
        if (IsValidKey(key)) {
            pressed_keys_[key] = state;
            if (state) {
                audio_graph::AudioBridge::TapDown(key);
            } else {
                audio_graph::AudioBridge::TapUp(key);
            }
            emit DataChanged();
        }
    }

    bool Piano::IsWhiteKey(int key) {
        return !IsBlackKey(key);
    }

    bool Piano::IsBlackKey(int key) {
        int key_code = key % kKeysPerOctave;
        return kKeyOrder[key_code] == Piano::kBlackKey;
    }
}
