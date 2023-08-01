//
// Created by wangrl2016 on 2023/6/26.
//

#ifndef CHARACTER_PROJECT_MODEL_H
#define CHARACTER_PROJECT_MODEL_H

#include <QVersionNumber>
#include "app/model/play_progress_model.h"
#include "app/model/track_container_model.h"

namespace app {
    class ProjectModel : public TrackContainerModel {
    Q_OBJECT
    public:
        ProjectModel();

        ~ProjectModel() override;

        void CreateNewProject();

        PlayProgressModel* play_progress_model() { return play_progress_model_; }

        TrackContainerModel* track_container_model() { return track_container_model_; }

    public slots:

        void ClearProject();

    private:
        bool loading_project_;

        PlayProgressModel* play_progress_model_;
        TrackContainerModel* track_container_model_;
    };
}

#endif //CHARACTER_PROJECT_MODEL_H
