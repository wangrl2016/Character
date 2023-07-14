//
// Created by wangrl2016 on 2023/6/26.
//

#include <glog/logging.h>
#include "app/model/clip/clip.h"
#include "app/model/track/track.h"
#include "app/model/track_container_model.h"
#include "app/model/track/instrument_track.h"

namespace app {
    // Create a new (empty) track object. The track object is the whole track,
    // linking its contents, its name, type, and so forth.
    //
    // @param type The type of track
    // @param tc The track container object to encapsulate in this track
    Track::Track(TrackType type, TrackContainerModel* tc) :
            Model(tc),
            type_(type),
            track_container_(tc),
            clip_vec_() {
        track_container_->AddTrack(this);
    }

    // Destroy this track.
    //
    // Delete the clips and remove this track from the track container.
    Track::~Track() {
        Lock();

        emit DestroyedTrack();

        while (!clip_vec_.isEmpty()) {
            delete clip_vec_.last();
        }

        track_container_->RemoveTrack(this);

        UnLock();
    }

    Track* Track::Create(TrackType type, TrackContainerModel* tc) {
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

    void Track::AddClip(Clip* clip) {

    }

    void Track::RemoveClip(Clip* clip) {

    }
}
