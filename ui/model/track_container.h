//
// Created by wangrl2016 on 2023/6/12.
//

#ifndef CHARACTER_TRACK_CONTAINER_H
#define CHARACTER_TRACK_CONTAINER_H

#include <QReadWriteLock>
#include "ui/model/model.h"

namespace ui {
    class Track;
    // Base class for all track containers like song editor.
    class TrackContainer : public Model {
    Q_OBJECT
    public:
        TrackContainer();

        ~TrackContainer() override;

        void AddTrack(Track* track);

        void RemoveTrack(Track* track);

        virtual void UpdateAfterTrackAdd();

        void ClearAllTracks();

        bool IsEmpty() const;

    signals:
        void TrackAdded(Track* track);

    protected:
        mutable QReadWriteLock tracks_mutex_;

    private:
        QVector<Track*> tracks_;

        friend class TrackContainerView;

        friend class Track;
    };
}

#endif //CHARACTER_TRACK_CONTAINER_H
