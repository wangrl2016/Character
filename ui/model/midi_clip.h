//
// Created by wr on 2023/6/17.
//

#ifndef CHARACTER_MIDI_CLIP_H
#define CHARACTER_MIDI_CLIP_H

#include "ui/model/clip.h"
#include "ui/model/note.h"

namespace ui {
    class InstrumentTrack;

    class MidiClip : public Clip {
    Q_OBJECT
    public:

        MidiClip(InstrumentTrack* instrument_track);

        MidiClip(const MidiClip* other);

        ~MidiClip() override;

        Note* AddNote(const Note& new_note, bool quant_pos = true);

        void RemoveNote(Note* note_to_del);

        void RearrangeAllNote();

        void ClearNotes();

        // Next/previous track based on position in the conainting track.
        MidiClip* PreviousMidiClip() const;

        MidiClip* NextMidiClip() const;

    private:

        InstrumentTrack* instrument_track_;

        QVector<Note> notes_;
    };
}

#endif //CHARACTER_MIDI_CLIP_H
