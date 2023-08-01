//
// Created by wangrl2016 on 2023/7/31.
//

#include <fstream>
#include <glog/logging.h>
#include <QFile>
#include "app/project/file/project_file_manager.h"

namespace app {
    std::shared_ptr<ProjectModel> ProjectFileManager::Parse(const QString& file_path) {
        if (!QFile::exists(file_path)) {
            LOG(ERROR) << "File " << file_path.toStdString() << " is not exist";
            return nullptr;
        }

        std::fstream input(std::string(file_path.toLocal8Bit()), std::ios::in | std::ios::binary);
        if (!input.is_open()) {
            LOG(ERROR) << "Open file " << file_path.toStdString() << " failed";
            return nullptr;
        }
    }

    bool ProjectFileManager::Write(const std::shared_ptr<ProjectModel>& model,
                                   const QString& file_path) {

    }
}