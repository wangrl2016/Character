//
// Created by wangrl2016 on 2023/7/31.
//

#ifndef CHARACTER_PROJECT_FILE_MANAGER_H
#define CHARACTER_PROJECT_FILE_MANAGER_H

#include "app/model/project_model.h"

namespace app {
    class ProjectFileManager {
    public:
        static std::shared_ptr<ProjectModel> Parse(const QString& file_path);

        static bool Write(const std::shared_ptr<ProjectModel>& model, const QString& file_path);
    };
}

#endif //CHARACTER_PROJECT_FILE_MANAGER_H
