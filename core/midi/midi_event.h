//
// Created by wangrl2016 on 2023/6/17.
//

#ifndef CHARACTER_MIDI_EVENT_H
#define CHARACTER_MIDI_EVENT_H

#include <cstdint>
#include "core/midi/midi.h"

namespace core {
    class MidiEvent {
    public:
        enum class Source {
            kInternal,
            kExternal,
        };

        MidiEvent(MidiEventType type,
                  int channel = 0,
                  int16_t param1 = 0,
                  int16_t param2 = 0,
                  const void* source_port = nullptr,
                  Source source = Source::kExternal) :
                type_(type),
                channel_(channel),
                sys_data_(nullptr),
                source_port_(source_port),
                source_(source) {
            data_.param[0] = param1;
            data_.param[1] = param2;
        }

        MidiEventType type() const { return type_; }

    private:
        MidiEventType type_;    // MIDI event type

        int channel_;           // MIDI channel

        union {
            int16_t param[2];       // first/second parameter
            uint8_t bytes[4];       // raw bytes
            int32_t sys_data_len;   // len of sys_data
        } data_;

        const char* sys_data_;
        const void* source_port_;
        Source source_;
    };
}

#endif //CHARACTER_MIDI_EVENT_H
