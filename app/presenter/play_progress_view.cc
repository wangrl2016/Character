//
// Created by wangrl2016 on 2023/6/23.
//

#include "app/presenter/play_progress_presenter.h"
#include "app/presenter/play_progress_view.h"

namespace app {
    void PlayProgressView::Subscribe(PlayProgressPresenter* presenter) {
        play_progress_presenter_ = presenter;
        presenter->AddView(this);
    }

    void PlayProgressView::PlayProgressUpdate() {

    }
}
