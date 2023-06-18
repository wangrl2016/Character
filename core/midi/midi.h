//
// Created by wangrl2016 on 2023/6/17.
//

#ifndef CHARACTER_MIDI_H
#define CHARACTER_MIDI_H

namespace core {
    enum MidiEventType {
        kMidiNoteOff = 0x80,
        kMidiNoteOn = 0x90,
        kMidiKeyPressure = 0xA0
    };
}

#endif //CHARACTER_MIDI_H
