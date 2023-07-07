//
// Created by wangrl2016 on 2023/7/7.
//

#ifndef CHARACTER_MODEL_H
#define CHARACTER_MODEL_H

#include <QObject>

namespace app {
    class Model : public QObject {
    Q_OBJECT
    public:
        explicit Model(Model* parent);

        ~Model() override = default;

    signals:
        // Emitted if actual of the model (e.g. values) have changed.
        void DataChanged();
    };
}

#endif //CHARACTER_MODEL_H
