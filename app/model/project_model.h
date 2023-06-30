//
// Created by wangrl2016 on 2023/6/26.
//

#ifndef CHARACTER_PROJECT_MODEL_H
#define CHARACTER_PROJECT_MODEL_H

#include "app/model/track_container.h"

namespace app {
    class ProjectModel : public TrackContainer {


    public:
        void CreateNewProject();
    };
}

#endif //CHARACTER_PROJECT_MODEL_H
