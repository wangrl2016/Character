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
        explicit Model(Model* parent, QString display_name = QString());

        [[nodiscard]] virtual QString display_name() const;

        virtual void set_display_name(const QString& display_name);

    signals:
        // emitted if actual data of the model (e.g. values) have changed
        void DataChanged();

        // emitted in case new data was not set as it's been equal to old data
        void DataUnchanged();

        // emitted if properties of the model (e.g. ranges) have changed
        void PropertiesChanged();

    private:
        QString display_name_;
    };
}

#endif //CHARACTER_MODEL_H
