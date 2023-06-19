//
// Created by wangrl2016 on 2023/6/17.
//

#include "ui/model/instrument_track.h"
#include "ui/model/midi_clip.h"

namespace ui {
    MidiClip::MidiClip(InstrumentTrack* instrument_track) :
            Clip(instrument_track) {}

    MidiClip::MidiClip(const MidiClip* other) :
        Clip(other->instrument_track_) {

    }

    MidiClip::~MidiClip() {

    }

    Note* MidiClip::AddNote(const Note& note, const bool quant_pos) {
        auto new_note = new Note(note);

        instrument_track_->Lock();
        notes_.insert(std::upper_bound(notes_.begin(),
                                       notes_.end(),
                                       new_note,
                                       Note::LessThan),
                      new_note);
        instrument_track_->Unlock();

        CheckType();

        UpdateLength();

        emit DataChanged();

        return new_note;
    }

    void MidiClip::CheckType() {
        auto iter = notes_.begin();
        while (iter != notes_.end()) {
            if ((*iter)->length() > 0) {
                set_clip_type(kMelodyClip);
                return;
            }
            iter++;
        }
        set_clip_type(kBeatClip);
    }


}