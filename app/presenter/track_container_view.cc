//
// Created by wangrl2016 on 2023/7/2.
//

#include "app/presenter/track_container_view.h"

namespace app {
    void TrackContainerView::Subscribe(TrackContainerPresenter* presenter) {
        track_container_presenter_ = presenter;
    }
}
