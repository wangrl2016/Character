//
// Created by wangrl2016 on 2023/6/11.
//

#include <utility>
#include "ui/model/model.h"

namespace ui {
    // Implementation of Model base class.
    Model::Model(Model* parent, QString display_name, bool default_constructed) :
            QObject(parent),
            display_name_(std::move(display_name)),
            default_constructed_(default_constructed) {}

    Model* Model::ParentModel() const {
        return dynamic_cast<Model*>(parent());
    }

    QString Model::display_name() const {
        return display_name_;
    }

    void Model::set_display_name(const QString& display_name) {
        display_name_ = display_name;
    }
}
