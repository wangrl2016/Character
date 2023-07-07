//
// Created by wangrl2016 on 2023/7/6.
//

#ifndef CHARACTER_MIDI_CLIP_H
#define CHARACTER_MIDI_CLIP_H

#include "app/model/clip/clip.h"
#include "app/model/music/note.h"

namespace app {
    class InstrumentTrack;

    class MidiClip : public Clip {
    Q_OBJECT
    public:
        enum MidiClipType {
            kBeatClip,
            kMelodyClip,
        };

        explicit MidiClip(InstrumentTrack* instrument_track);

        MidiClip(const MidiClip& other);

        ~MidiClip() override;

        void Init();

        void UpdateLength();

        Note* AddNote(const Note& note, bool quant_pos = true);

        void RemoveNote(Note* note_to_del);

    private:
        void SetType(MidiClipType clip_type);

        void CheckType();

        InstrumentTrack* instrument_track_;
        MidiClipType clip_type_;
        QVector<Note*> note_vec_;
    };
}

#endif //CHARACTER_MIDI_CLIP_H
