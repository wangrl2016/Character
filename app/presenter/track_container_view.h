//
// Created by wr on 2023/7/2.
//

#ifndef CHARACTER_TRACK_CONTAINER_VIEW_H
#define CHARACTER_TRACK_CONTAINER_VIEW_H

namespace app {
    class TrackContainerPresenter;

    class TrackContainerView {
    public:
        void Subscribe(TrackContainerPresenter* presenter);

    protected:
        TrackContainerPresenter* track_container_presenter_ = nullptr;
    };
}

#endif //CHARACTER_TRACK_CONTAINER_VIEW_H
