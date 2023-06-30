//
// Created by wr on 2023/6/26.
//

#ifndef CHARACTER_TRACK_CONTAINER_H
#define CHARACTER_TRACK_CONTAINER_H

#include <memory>
#include <QVector>
#include <QObject>
#include <QReadWriteLock>
#include "app/model/track/track.h"

namespace app {
    class Track;

    class TrackContainer : public QObject {
    Q_OBJECT
    public:
        TrackContainer();

        void AddTrack(Track* track);

        void RemoveTrack(Track* track);

        bool Empty() const;

        int TrackSize(Track::TrackType type = Track::kTrackCount) const;

        void ClearAllTracks();

    protected:
        mutable QReadWriteLock track_mutex_;

    private:
        QVector<Track*> track_vec_;
    };
}

#endif //CHARACTER_TRACK_CONTAINER_H
