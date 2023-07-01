//
// Created by wangrl2016 on 2023/6/26.
//

#ifndef CHARACTER_PROJECT_MODEL_H
#define CHARACTER_PROJECT_MODEL_H

#include "app/model/track_container.h"
#include "play_progress_model.h"

namespace app {
    class ProjectModel : public TrackContainer {
    Q_OBJECT
    public:
        ProjectModel();

        ~ProjectModel();

        void CreateNewProject();

        PlayProgressModel* play_progress_model() { return play_progress_model_; }

    public slots:
        void ClearProject();

    private:
        bool loading_project_;

        PlayProgressModel* play_progress_model_;


    };
}

#endif //CHARACTER_PROJECT_MODEL_H
