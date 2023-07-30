//
// Created by wangrl2016 on 2023/6/30.
//

#ifndef CHARACTER_CONFIG_MANAGER_H
#define CHARACTER_CONFIG_MANAGER_H

#include <QObject>

namespace app {
    const QString kProjectPath = "project";
    const QString kTemplatePath = "template";

    class ConfigManager : public QObject {
    Q_OBJECT
    public:
        static inline ConfigManager* Instance() {
            if (instance_ == nullptr) {
                instance_ = new ConfigManager();
            }
            return instance_;
        }

        [[nodiscard]] const QString& working_dir() const {
            return working_dir_;
        }

        [[nodiscard]] QString ProjectDir() const {
            return working_dir() + QDir::separator() + kProjectPath;
        }

        [[nodiscard]] QString TemplateDir() const {
            return working_dir() + QDir::separator() + kTemplatePath;
        }

        static QString DefaultVersion();

        static QString ProjectName();

        void InitInstalledWorkingDir();

        // Creates the working directory & subdirectories on disk.
        void CreateWorkingDir();

    private:
        ConfigManager();

        ConfigManager(const ConfigManager& c);

        ~ConfigManager() override;

        static ConfigManager* instance_;
        QString version_;
        QString working_dir_;
    };

}


#endif //CHARACTER_CONFIG_MANAGER_H
