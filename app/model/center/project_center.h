//
// Created by wangrl2016 on 2023/7/28.
//

#ifndef CHARACTER_PROJECT_CENTER_H
#define CHARACTER_PROJECT_CENTER_H

#include <QString>

namespace app {
    class ProjectCenter : public QObject {
    Q_OBJECT
    public:
        void OpenProjectWithPath(const QString& path);

    signals:
        void SignalOpenProjectFailed(const QString& tips);
    };
}


#endif //CHARACTER_PROJECT_CENTER_H
