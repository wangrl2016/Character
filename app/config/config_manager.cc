//
// Created by wangrl2016 on 2023/6/30.
//

#include <QDir>
#include <QStandardPaths>
#include "config/user_config.h"
#include "app/config/config_manager.h"

namespace app {
    ConfigManager* ConfigManager::instance_ = nullptr;

    ConfigManager::ConfigManager() : version_(DefaultVersion()) {
        InitInstalledWorkingDir();
    }

    QString ConfigManager::DefaultVersion() {
        return QString::number(PROJECT_VERSION_MAJOR) + "." +
               QString::number(PROJECT_VERSION_MINOR) + "." +
               QString::number(PROJECT_VERSION_PATCH);
    }

    QString ConfigManager::ProjectName() {
        return PROJECT_NAME;
    }

    void ConfigManager::InitInstalledWorkingDir() {
        working_dir_ = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/character/";
    }

    void ConfigManager::CreateWorkingDir() {
        QDir().mkpath(working_dir_);
    }
}
