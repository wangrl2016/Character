//
// Created by wangrl2016 on 2023/6/11.
//

#include "ui/model/instrument_track.h"
#include "ui/model/song.h"

namespace ui {
    InstrumentTrack::InstrumentTrack(TrackContainer* tc) :
            Track(Track::kInstrumentTrack, tc),
            piano_(this) {

    }

    InstrumentTrack::~InstrumentTrack() = default;

    void InstrumentTrack::ProcessInEvent(const core::MidiEvent& event, int time, int offset) {
//        if (Song::Instance()->exporting()) {
//            return;
//        }

    }

    void InstrumentTrack::ProcessOutEvent(const core::MidiEvent& event, int time, int offset) {

    }
}
