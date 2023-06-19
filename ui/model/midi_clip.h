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
        enum ClipType {
            kBeatClip,
            kMelodyClip,
        };

        MidiClip(InstrumentTrack* instrument_track);

        MidiClip(const MidiClip* other);

        ~MidiClip() override;

        void Init();

        void UpdateLength();

        Note* AddNote(const Note& note, bool quant_pos = true);

        void RemoveNote(Note* note_to_del);

        Note* NoteAtStep(int step);

        void RearrangeAllNotes();

        void ClearNotes();

        [[nodiscard]] inline const QVector<Note*>& notes() const { return notes_; }

        Note* AddStepNote(int step);

        void SetStep(int step, bool enabled);

        // Split the list of notes on the given position.
        void SplitNotes(QVector<Note*> notes, int pos);

        inline ClipType clip_type() const { return clip_type_; }

        // Next/previous track based on position in the containing track.
        MidiClip* PreviousMidiClip() const;

        MidiClip* NextMidiClip() const;

        inline InstrumentTrack* instrument_track() const {
            return instrument_track_;
        }

        bool Empty();

    protected:
        void UpdateTrack();

    public slots:
        void AddSteps();

    private:

        void set_clip_type(ClipType type) {
            clip_type_ = type;
        }

        void CheckType();

        InstrumentTrack* instrument_track_;

        ClipType clip_type_;
        QVector<Note*> notes_;
    };
}

#endif //CHARACTER_MIDI_CLIP_H
