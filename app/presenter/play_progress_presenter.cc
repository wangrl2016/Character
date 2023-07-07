//
// Created by wangrl2016 on 2023/6/23.
//

#include "app/presenter/play_progress_presenter.h"
#include "module/audio_graph/audio_bridge.h"

namespace app {
    PlayProgressPresenter::PlayProgressPresenter(PlayProgressModel* model) :
            model_(model) {
    }

    PlayProgressPresenter::~PlayProgressPresenter() {

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

    void PlayProgressPresenter::NotifyLoop(bool loop) {
        model_->set_loop(loop);
        for (auto& view : view_list_) {
            view->LoopUpdate();
        }
    }

    void PlayProgressPresenter::NotifyLoopStart(double loop_start) {
        model_->set_loop_start(loop_start);
        for (auto& view : view_list_) {
            view->LoopStartUpdate();
        }
    }

    void PlayProgressPresenter::NotifyLoopEnd(double loop_end) {
        model_->set_loop_end(loop_end);
        for (auto& view : view_list_) {
            view->LoopEndUpdate();
        }
    }

    double PlayProgressPresenter::PlayProgress() const {
        if (model_)
            return model_->play_progress();
        else
            return 0.0;
    }

    double PlayProgressPresenter::LoopStart() const {
        if (model_)
            return model_->loop_start();
        else
            return 0.0;
    }

    double PlayProgressPresenter::LoopEnd() const {
        if (model_)
            return model_->loop_end();
        else
            return 0.0;
    }
}
