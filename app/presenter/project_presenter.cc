//
// Created by wangrl2016 on 2023/7/1.
//

#include "app/presenter/project_presenter.h"

namespace app {
    ProjectPresenter* ProjectPresenter::Instance() {
        static auto* instance = new ProjectPresenter;
        return instance;
    }

    void ProjectPresenter::SetModel(ProjectModel* model) {
        play_progress_presenter_ = new PlayProgressPresenter(model->play_progress_model());
        track_container_presenter_ = new TrackContainerPresenter(model->track_container_model());
    }

    ProjectPresenter::ProjectPresenter() = default;

    ProjectPresenter::~ProjectPresenter() {
        delete play_progress_presenter_;
        delete track_container_presenter_;
    }
}
