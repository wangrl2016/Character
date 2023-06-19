//
// Created by wangrl2016 on 2023/6/11.
//

#include "ui/model/track.h"
#include "instrument_track.h"

namespace ui {
    Track::Track(TrackType type, TrackContainer* tc) :
            Model(nullptr),
            track_container_(tc),
            type_(type),
            name_() {

    }

    Track::~Track() = default;

    // Create a track based on the given track type and container.
    //
    // @param type the type of track to create
    // @param tc the track container to attach to
    Track* Track::Create(TrackType type, TrackContainer* tc) {
        Track* t = nullptr;
        switch (type) {
            case kInstrumentTrack:
                t = new InstrumentTrack(tc);
                break;
            default:
                break;
        }

        tc->UpdateAfterTrackAdd();

        return t;
    }

    Track* Track::Clone() {
        return nullptr;
    }
}
