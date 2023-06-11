//
// Created by wangrl2016 on 2023/6/11.
//

#ifndef CHARACTER_SONG_H
#define CHARACTER_SONG_H

#include <QString>

namespace ui {
    class Song {
    public:

        // file management
        void CreateNewProject();

        void CreateNewProjectFromTemplate(const QString* templ);

        void LoadProject(const QString& filename);

        bool SaveProject();

        bool SaveProjectAs(const QString& filename);

        bool SaveProjectFile(const QString& filename, bool with_resource = false);

        [[nodiscard]] const QString& project_file_name() const {
            return project_file_name_;
        }

        [[nodiscard]] bool IsLoadingProject() const {
            return loading_project_;
        }

    private slots:
        void MasterVolumeChanged();

    private:
        QString project_file_name_;
        bool loading_project_;
    };
}

#endif //CHARACTER_SONG_H
