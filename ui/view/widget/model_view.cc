//
// Created by wangrl2016 on 2023/6/12.
//

#include <utility>
#include "ui/view/widget/model_view.h"

namespace ui {
    ModelView::ModelView(std::shared_ptr<Model> model,
                         std::shared_ptr<QWidget> widget) :
            model_(std::move(model)),
            widget_(std::move(widget)) {

    }

    ModelView::~ModelView() {

    }

    void ModelView::SetModel(std::shared_ptr<Model> model,
                             bool is_old_model_valid) {

    }

    void ModelView::UnsetModel() {

    }

    void ModelView::DoConnections() {

    }
}
