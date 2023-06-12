//
// Created by wangrl2016 on 2023/6/11.
//

#include "ui/model/model.h"

#include <utility>

namespace ui {
    Model::Model(Model* parent, QString display_name) :
            QObject(parent), display_name_(std::move(display_name)) {

    }

    QString Model::display_name() const {
        return display_name_;
    }

    void Model::set_display_name(const QString& display_name) {
        display_name_ = display_name;
    }
}
