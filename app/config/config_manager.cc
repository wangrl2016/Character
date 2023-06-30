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
        return QString::number(CHARACTER_VERSION_MAJOR) + "." +
               QString::number(CHARACTER_VERSION_MINOR) + "." +
               QString::number(CHARACTER_VERSION_PATCH);
    }

    void ConfigManager::InitInstalledWorkingDir() {
        working_dir_ = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/character/";
    }

    void ConfigManager::CreateWorkingDir() {
        QDir().mkpath(working_dir_);
    }
}
