//
// Created by wangrl2016 on 2023/6/17.
//

#ifndef CHARACTER_MIDI_EVENT_PROCESSOR_H
#define CHARACTER_MIDI_EVENT_PROCESSOR_H

#include "core/midi/midi_event.h"

namespace core {
    // All classes being able to process MIDI events should inherit from this.
    class MidiEventProcessor {
    public:
        MidiEventProcessor() = default;

        virtual ~MidiEventProcessor() = default;

        virtual void ProcessInEvent(const MidiEvent& event, int time, int offset = 0) = 0;

        virtual void ProcessOutEvent(const MidiEvent& event, int time, int offset = 0) = 0;
    };
}

#endif //CHARACTER_MIDI_EVENT_PROCESSOR_H
