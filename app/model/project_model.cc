//
// Created by wangrl2016 on 2023/6/26.
//

#include "app/model/project_model.h"

namespace app {
    ProjectModel::ProjectModel() :
            TrackContainer(),
            loading_project_(false) {

    }


    void ProjectModel::CreateNewProject() {
        loading_project_ = true;

        ClearProject();

        // Create a track based on the given track type and container.
        //
        // @param tt
        Track::Create(Track::kInstrumentTrack, this);

        loading_project_ = false;
    }

    void ProjectModel::ClearProject() {

    }
}
