//
// Created by wr on 2023/6/11.
//

#include "ui/model/song.h"
#include "ui/model/track.h"

namespace ui {

    Song::Song() :
        TrackContainer() {

    }

    Song::Song(const Song& song) {

    }

    Song::~Song() {

    }

    void Song::CreateNewProject() {
        loading_project_ = true;

        ClearProject();

        set_project_file_name("");

        Track* t;
        t = Track::Create(Track::kInstrumentTrack, this);

    }

    void Song::CreateNewProjectFromTemplate(const QString* templ) {

    }

    void Song::LoadProject(const QString& filename) {

    }

    bool Song::SaveProject() {

    }

    bool Song::SaveProjectAs(const QString& filename) {

    }

    bool Song::SaveProjectFile(const QString& filename, bool with_resource) {

    }

    void Song::ClearProject() {

    }

    void Song::set_project_file_name(const QString& project_file_name) {
        if (project_file_name != project_file_name_) {
            project_file_name_ = project_file_name;
            emit ProjectFileNameChanged();
        }
    }

    void Song::MasterVolumeChanged() {

    }
}
