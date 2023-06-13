//
// Created by wangrl2016 on 2023/6/11.
//

#ifndef CHARACTER_SONG_H
#define CHARACTER_SONG_H

#include <QString>
#include "ui/model/track_container.h"

namespace ui {
    // Song -> Track -> Clip -> Fragment or Note -> Syllable -> Phone
    class Song : public TrackContainer {
    Q_OBJECT
    public:
        Song();

        Song(const Song& song);

        ~Song() override;

        // file management
        void CreateNewProject();

        void CreateNewProjectFromTemplate(const QString* templ);

        void LoadProject(const QString& filename);

        bool SaveProject();

        bool SaveProjectAs(const QString& filename);

        bool SaveProjectFile(const QString& filename, bool with_resource = false);

        void ClearProject();

        [[nodiscard]] const QString& project_file_name() const {
            return project_file_name_;
        }

        void set_project_file_name(const QString& project_file_name);

        [[nodiscard]] bool IsLoadingProject() const {
            return loading_project_;
        }
    signals:
        void ProjectLoaded();

        void ProjectFileNameChanged();

    private slots:
        void MasterVolumeChanged();

    private:
        QString project_file_name_;
        bool loading_project_;
    };
}

#endif //CHARACTER_SONG_H
