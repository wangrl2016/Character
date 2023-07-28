//
// Created by wangrl2016 on 2023/7/28.
//

#include <glog/logging.h>
#include <QFileInfo>
#include "app/model/center/project_center.h"

namespace app {
    void ProjectCenter::OpenProjectWithPath(const QString& path) {
        if (!QFileInfo::exists(path)) {
            QString error_message = QString("Project path ") + path + QString(" is not exist");
            LOG(ERROR) << error_message.toStdString();
            emit SignalOpenProjectFailed(error_message);
            return;
        }


    }
}
