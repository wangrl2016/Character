//
// Created by wangrl2016 on 2023/6/30.
//

#ifndef CHARACTER_INSTRUMENT_TRACK_H
#define CHARACTER_INSTRUMENT_TRACK_H

#include "app/model/track/track.h"

namespace app {
    class InstrumentTrack : public Track {
    Q_OBJECT
    public:
        InstrumentTrack(TrackContainerModel* tc);

        ~InstrumentTrack();
    };
}


#endif //CHARACTER_INSTRUMENT_TRACK_H
