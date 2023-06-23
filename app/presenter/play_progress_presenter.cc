//
// Created by wangrl2016 on 2023/6/23.
//

#include "app/presenter/play_progress_presenter.h"
#include "module/audio_graph/audio_bridge.h"

namespace app {
    PlayProgressPresenter::PlayProgressPresenter(PlayProgressModel* model) :
            model_(model) {
    }

    void PlayProgressPresenter::AddView(PlayProgressView* view) {
        view_list_.append(view);
    }

    void PlayProgressPresenter::NotifyPlayProgress(double sec) {
        model_->set_play_progress(sec);
        for (auto& view : view_list_) {
            view->PlayProgressUpdate();
        }
    }

    double PlayProgressPresenter::PlayProgress() const {
        if (model_)
            return model_->play_progress();
        else
            return 0.0;
    }
}
