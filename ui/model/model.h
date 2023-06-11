//
// Created by wangrl2016 on 2023/6/11.
//

#ifndef CHARACTER_MODEL_H
#define CHARACTER_MODEL_H

#include <QObject>

namespace ui {
    class Model : public QObject {
        Q_OBJECT
    public:

    signals:
        void DataChanged();
    };
}

#endif //CHARACTER_MODEL_H
