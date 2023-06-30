//
// Created by wangrl2016 on 2023/6/26.
//

#include "app/model/track/track.h"
#include "app/model/track_container.h"
#include "app/model/track/instrument_track.h"

namespace app {
    // Create a new (empty) track object. The track object is the whole track,
    // linking its contents, its name, type, and so forth.
    //
    // @param type The type of track
    // @param tc The track container object to encapsulate in this track
    Track::Track(TrackType type, TrackContainer* tc) :
            type_(type),
            track_container_(tc),
            clip_vec_() {
        track_container_->AddTrack(this);
    }

    Track* Track::Create(TrackType type, TrackContainer* tc) {
        Track* t = nullptr;

        switch (type) {
            case kInstrumentTrack:
                t = new InstrumentTrack(tc);
                break;
            default:
                break;
        }

        return t;
    }
}
