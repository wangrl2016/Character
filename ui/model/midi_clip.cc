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

    Note* MidiClip::AddNote(const Note& new_note, const bool quant_pos) {
        return nullptr;
    }


}