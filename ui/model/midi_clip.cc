//
// Created by wangrl2016 on 2023/6/17.
//

#include "ui/model/instrument_track.h"
#include "ui/model/midi_clip.h"
#include "ui/view/widget/midi_clip_view.h"

namespace ui {
    MidiClip::MidiClip(InstrumentTrack* instrument_track) :
            Clip(instrument_track) {
        Init();
    }

    MidiClip::MidiClip(const MidiClip* other) :
        Clip(other->instrument_track_) {
        for (const auto& note : other->notes_) {
            notes_.push_back(new Note(*note));
        }

        Init();

        // SetAutoSize(true);
    }

    MidiClip::~MidiClip() {
        // emit DestroyedMidiClip(this);

        for (const auto& note : notes_) {
            delete note;
        }

        notes_.clear();
    }

    void MidiClip::Init() {

    }

    void MidiClip::UpdateLength() {

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

    void MidiClip::RemoveNote(Note* note_to_del) {
        instrument_track()->Lock();
        QVector<Note*>::ConstIterator iter = notes_.cbegin();
        while (iter != notes_.end()) {
            if (*iter == note_to_del) {
                delete *iter;
                notes_.erase(iter);
            }
            iter++;
        }
        instrument_track()->Unlock();

        CheckType();

        UpdateLength();

        emit DataChanged();
    }

    Note* MidiClip::NoteAtStep(int step) {
        return nullptr;
    }

    void MidiClip::RearrangeAllNotes() {
        std::sort(notes_.begin(), notes_.end(), Note::LessThan);
    }

    void MidiClip::ClearNotes() {
        instrument_track()->Lock();
        for (const auto& note : notes_) {
            delete note;
        }
        notes_.clear();
        instrument_track()->Unlock();

        CheckType();

        emit DataChanged();
    }

    Note* MidiClip::AddStepNote(int step) {
        return nullptr;
    }

    void MidiClip::SetStep(int step, bool enabled) {

    }

    void MidiClip::SplitNotes(QVector<Note*> notes, int pos) {

    }

    MidiClip* MidiClip::PreviousMidiClip() const {

    }

    MidiClip* MidiClip::NextMidiClip() const {

    }

    bool MidiClip::Empty() {

    }

    ClipView* MidiClip::CreateView(TrackView* tv) {
        return new MidiClipView(this, tv);
    }

    void MidiClip::UpdateTrack() {

    }

    void MidiClip::AddSteps() {

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