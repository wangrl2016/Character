//
// Created by wangrl2016 on 2023/6/26.
//

#include "app/model/track_container_model.h"

namespace app {
    TrackContainerModel::TrackContainerModel() :
            Model(nullptr),
            track_mutex_(),
            track_vec_() {

    }

    void TrackContainerModel::AddTrack(Track* track) {
        track_mutex_.lockForWrite();
        track_vec_.push_back(track);
        track_mutex_.unlock();
    }

    void TrackContainerModel::RemoveTrack(Track* track) {
        QWriteLocker lock(&track_mutex_);
        auto index = track_vec_.indexOf(track);
        if (index != -1) {
            // If the track is solo, all other tracks are mute. Change this before
            // removing the solo track.
            if (track->solo()) {
                track->set_solo(false);
            }
            track_vec_.remove(index);
            lock.unlock();
        }
    }

    bool TrackContainerModel::Empty() const {

    }

    int TrackContainerModel::TrackSize(Track::TrackType type) const {
        int cnt = 0;
        track_mutex_.lockForRead();
        for (const auto& track: track_vec_) {
            if (track->type() == type || type == Track::kTrackCount) {
                cnt++;
            }
        }
        track_mutex_.unlock();
        return cnt;
    }

    void TrackContainerModel::ClearAllTracks() {
        while (!track_vec_.isEmpty()) {
            delete track_vec_.first();
        }
    }

    void TrackContainerModel::AddClip(Track* track, Clip* clip) {

    }

    void TrackContainerModel::RemoveClip(Track* track, Clip* clip) {

    }

    int TrackContainerModel::ClipSize(Track* track) const {
    }
}
