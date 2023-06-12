//
// Created by wangrl2016 on 2023/6/12.
//

#ifndef CHARACTER_TRACK_CONTAINER_H
#define CHARACTER_TRACK_CONTAINER_H

#include "ui/model/model.h"
#include "ui/model/track.h"

namespace ui {
    class TrackContainer : public Model {
    public:
        TrackContainer();

        ~TrackContainer() override;

        void AddTrack(std::shared_ptr<Track> track);

        void RemoveTrack(std::shared_ptr<Track> track);

        void ClearAllTracks();

        bool IsEmpty() const;

    signals:
        void TrackAdded(std::shared_ptr<Track> track);


    private:
        QVector<std::shared_ptr<Track>> tracks_;
    };
}

#endif //CHARACTER_TRACK_CONTAINER_H
