//
// Created by wangrl2016 on 2023/6/26.
//

#include "app/model/project_model.h"

namespace app {
    ProjectModel::ProjectModel() :
            TrackContainerModel(),
            loading_project_(false) {
        play_progress_model_ = new PlayProgressModel();
        track_container_model_ = new TrackContainerModel();
    }

    ProjectModel::~ProjectModel() {
        delete play_progress_model_;
        delete track_container_model_;
    }

    void ProjectModel::CreateNewProject() {
        loading_project_ = true;

        ClearProject();

        // Create a track based on the given track type and container.
        //
        // @param tt
        Track::Create(Track::kInstrumentTrack, track_container_model_);

        loading_project_ = false;
    }

    void ProjectModel::ClearProject() {

    }
}
