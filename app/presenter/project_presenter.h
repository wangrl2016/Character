//
// Created by wangrl2016 on 2023/7/1.
//

#ifndef CHARACTER_PROJECT_PRESENTER_H
#define CHARACTER_PROJECT_PRESENTER_H

#include <QObject>
#include "app/model/project_model.h"
#include "app/presenter/play_progress_presenter.h"
#include "app/presenter/track_container_presenter.h"

namespace app {
    class ProjectPresenter : QObject {
    Q_OBJECT
    public:
        explicit ProjectPresenter(ProjectModel* model);

        ~ProjectPresenter() override;

        PlayProgressPresenter* play_progress_presenter() { return play_progress_presenter_; }

        TrackContainerPresenter* track_container_presenter() { return track_container_presenter_; }
    private:
        PlayProgressPresenter* play_progress_presenter_;
        TrackContainerPresenter* track_container_presenter_;
    };
}

#endif //CHARACTER_PROJECT_PRESENTER_H
