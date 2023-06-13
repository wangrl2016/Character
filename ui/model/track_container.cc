//
// Created by wangrl2016 on 2023/6/12.
//

#include "ui/model/track_container.h"

namespace ui {
    TrackContainer::TrackContainer() :
            Model(nullptr), tracks_mutex_(), tracks_() {}

    TrackContainer::~TrackContainer() {
        ClearAllTracks();
    }

    void TrackContainer::AddTrack(Track* track) {
        track->Lock();
        tracks_mutex_.lockForWrite();
        tracks_.push_back(track);
        tracks_mutex_.unlock();
        track->Unlock();
        emit TrackAdded(track);
    }

    void TrackContainer::RemoveTrack(Track* track) {

    }

    void TrackContainer::UpdateAfterTrackAdd() {

    }

    void TrackContainer::ClearAllTracks() {

    }

    bool TrackContainer::IsEmpty() const {
        return false;
    }
}
