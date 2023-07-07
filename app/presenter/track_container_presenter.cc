//
// Created by wangrl2016 on 2023/7/2.
//

#include "app/presenter/track_container_presenter.h"

namespace app {
    TrackContainerPresenter::TrackContainerPresenter(TrackContainerModel* model) :
        track_container_model_(model) {

    }

    void TrackContainerPresenter::AddView(TrackContainerView* view) {
        view_list_.append(view);
    }
}
