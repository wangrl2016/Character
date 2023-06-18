//
// Created by wangrl2016 on 2023/6/10.
//

#ifndef CHARACTER_PIANO_H
#define CHARACTER_PIANO_H

#include "core/midi/midi_event_processor.h"
#include "ui/model/model.h"
#include "ui/model/note.h"

namespace ui {
    class InstrumentTrack;

    class Piano : public Model {
    public:
        static const int kWhiteKeysPerOctave = 7;
        static const int kBlackKeysPerOctave = 5;
        // total 128
        static const int kNumWhiteKeys = 75;
        static const int kNumBlackKeys = 53;

        enum KeyType {
            kWhiteKey,
            kBlackKey,
        };

        explicit Piano(InstrumentTrack* track);

        // Turn a key on or off.
        // @param key   the key number to change
        // @param state the state to set the key to
        void SetKeyState(int key, bool state);

        [[nodiscard]] bool IsKeyPressed(int key) const {
            return pressed_keys_[key];
        }

        void HandleKeyPress(int key, int midi_velocity = -1);

        void HandleKeyRelease(int key);

        InstrumentTrack* instrument_track() const {
            return instrument_track_;
        }

        static bool IsWhiteKey(int key);

        static bool IsBlackKey(int key);

    private:
        static bool IsValidKey(int key) {
            return 0 <= key && key < kNumKeys;
        }

        InstrumentTrack* instrument_track_;
        core::MidiEventProcessor* midi_event_processor_;

        // key is pressed or not?
        std::array<bool, kNumKeys> pressed_keys_ = {};
    };
}


#endif //CHARACTER_PIANO_H
