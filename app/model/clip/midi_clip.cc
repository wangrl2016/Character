//
// Created by wangrl2016 on 2023/7/6.
//

#include "app/model/clip/midi_clip.h"
#include "app/model/track/instrument_track.h"

namespace app {
    MidiClip::MidiClip(InstrumentTrack* instrument_track) :
            Clip(instrument_track),
            instrument_track_(instrument_track),
            clip_type_(kBeatClip) {

    }

    MidiClip::MidiClip(const MidiClip& other) :
            Clip(other.instrument_track_){

    }


}
