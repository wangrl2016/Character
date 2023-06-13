//
// Created by wangrl2016 on 2023/6/11.
//

#include "ui/model/instrument_track.h"

namespace ui {
    InstrumentTrack::InstrumentTrack(TrackContainer* tc) :
            Track(Track::kInstrumentTrack, tc) {

    }

    InstrumentTrack::~InstrumentTrack() = default;
}
