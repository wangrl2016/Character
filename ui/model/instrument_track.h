//
// Created by wangrl2016 on 2023/6/11.
//

#ifndef CHARACTER_INSTRUMENT_TRACK_H
#define CHARACTER_INSTRUMENT_TRACK_H

#include "core/midi/midi_event_processor.h"
#include "ui/model/track.h"
#include "ui/model/track_container.h"
#include "ui/model/note.h"
#include "ui/model/piano.h"

namespace ui {
    class Instrument;

    class InstrumentTrack : public Track, public core::MidiEventProcessor {
    public:
        InstrumentTrack(TrackContainer* tc);

        ~InstrumentTrack() override;

        void ProcessInEvent(const core::MidiEvent& event,
                            int time,
                            int offset = 0) override;

        void ProcessOutEvent(const core::MidiEvent& event,
                             int time,
                             int offset = 0) override;

        Clip* CreateClip(int pos) override;

    signals:
        void InstrumentChanged();

        void MidiNoteOn(const Note& note);

        void MidiNoteOff(const Note& note);

        void NameChanged();

        void NewNote();

        void EndNote();

    protected slots:


    private:
        Instrument* instrument_;

        Piano piano_;

        int base_note_;     // The "A4" or "440Hz" key (default 69)

        float volume_;
        float panning_;
    };
}

#endif //CHARACTER_INSTRUMENT_TRACK_H
