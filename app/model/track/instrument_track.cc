//
// Created by wangrl2016 on 2023/6/30.
//

#include "app/model/track/instrument_track.h"

namespace app {
    InstrumentTrack::InstrumentTrack(TrackContainerModel* tc) :
            Track(Track::kInstrumentTrack, tc) {

    }

    InstrumentTrack::~InstrumentTrack() {

    }
}
