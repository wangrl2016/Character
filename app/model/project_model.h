//
// Created by wangrl2016 on 2023/6/26.
//

#ifndef CHARACTER_PROJECT_MODEL_H
#define CHARACTER_PROJECT_MODEL_H

#include "app/model/track_container.h"

namespace app {
    class ProjectModel : public TrackContainer {
    Q_OBJECT
    public:
        ProjectModel();

        void CreateNewProject();

    public slots:
        void ClearProject();

    private:
        bool loading_project_;

    };
}

#endif //CHARACTER_PROJECT_MODEL_H
