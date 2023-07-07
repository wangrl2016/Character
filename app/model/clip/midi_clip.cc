//
// Created by wangrl2016 on 2023/7/6.
//

#include "app/model/music/note.h"
#include "app/model/clip/midi_clip.h"
#include "app/model/track/instrument_track.h"

namespace app {
    MidiClip::MidiClip(InstrumentTrack* instrument_track) :
            Clip(instrument_track),
            instrument_track_(instrument_track),
            clip_type_(kBeatClip) {

    }

    MidiClip::MidiClip(const MidiClip& other) :
            Clip(other.instrument_track_) {

    }

    MidiClip::~MidiClip() {

    }

    void MidiClip::Init() {

    }

    void MidiClip::UpdateLength() {

    }

    Note* MidiClip::AddNote(const Note& note, const bool quant_pos) {
        auto new_note = new Note(note);

        instrument_track_->Lock();
        note_vec_.insert(std::upper_bound(note_vec_.cbegin(),
                                          note_vec_.cend(),
                                          new_note,
                                          Note::LessThan),
                         new_note);
        instrument_track_->UnLock();

        CheckType();
        UpdateLength();

        // emit DataChanged();

        return new_note;
    }

    void MidiClip::RemoveNote(Note* note_to_del) {
        instrument_track_->Lock();
        auto it = note_vec_.cbegin();
        while (it != note_vec_.cend()) {
            if (*it == note_to_del) {
                delete *it;
                note_vec_.erase(it);
                break;
            }
            it++;
        }
        instrument_track_->UnLock();

        CheckType();
        UpdateLength();

        // emit DataChanged();
    }

    void MidiClip::SetType(MidiClipType clip_type) {
        clip_type_ = clip_type;
    }

    void MidiClip::CheckType() {
        auto it = note_vec_.begin();
        while (it != note_vec_.end()) {
            if ((*it)->length() > 0) {
                SetType(kMelodyClip);
                return;
            }
            it++;
        }
        SetType(kBeatClip);
    }
}
