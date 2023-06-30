//
// Created by wangrl2016 on 2023/6/30.
//

#ifndef CHARACTER_CONFIG_MANAGER_H
#define CHARACTER_CONFIG_MANAGER_H

#include <QObject>

namespace app {
    class ConfigManager : public QObject {
    public:
        static inline ConfigManager* Instance() {
            if (instance_ == nullptr) {
                instance_ = new ConfigManager();
            }
            return instance_;
        }

        static QString DefaultVersion() ;

        void InitInstalledWorkingDir();

        // Creates the working directory & subdirectories on disk.
        void CreateWorkingDir();

    private:
        ConfigManager();

        static ConfigManager* instance_;
        QString version_;
        QString working_dir_;
    };

}


#endif //CHARACTER_CONFIG_MANAGER_H
