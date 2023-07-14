//
// Created by wangrl2016 on 2023/7/2.
//

#ifndef CHARACTER_TRACK_CONTAINER_PRESENTER_H
#define CHARACTER_TRACK_CONTAINER_PRESENTER_H

#include "app/model/track_container_model.h"
#include "app/presenter/track_container_subscriber.h"
#include "app/presenter/track_container_view.h"

namespace app {
    class TrackContainerPresenter : public TrackContainerSubscriber {
    public:
        explicit TrackContainerPresenter(TrackContainerModel* model);

        void AddView(TrackContainerView* view);

        int TrackSize(Track::TrackType type = Track::TrackType::kTrackCount) {
            return track_container_model_->TrackSize(type);
        }
    private:
        TrackContainerModel* track_container_model_;

        QList<TrackContainerView*> view_list_;
    };
}

#endif //CHARACTER_TRACK_CONTAINER_PRESENTER_H
