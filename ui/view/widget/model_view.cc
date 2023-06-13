//
// Created by wangrl2016 on 2023/6/12.
//

#include "ui/view/widget/model_view.h"

namespace ui {
    ModelView::ModelView(Model* model, QWidget* widget) :
            model_(model),
            widget_(widget) {}

    ModelView::~ModelView() {
        if (model_ != nullptr && model_->default_constructed()) {
            delete model_;
        }
    }

    void ModelView::SetModel(Model* model,
                             bool is_old_model_valid) {
        if (is_old_model_valid && model_ != nullptr) {
            if (model_->default_constructed()) {
                delete model_;
            } else {
                // signals and slot
                model_->disconnect(widget());
            }
        }

        model_ = model;

        DoConnections();

        widget()->update();

        ModelChanged();
    }

    // Unsets the current model by setting a dummy empty model.
    // The dummy model is marked as default constructed, so the next call to SetModel
    // will delete it.
    void ModelView::UnsetModel() {
        SetModel(new Model(nullptr, QString(), true));
    }

    void ModelView::DoConnections() {
        if (model_ != nullptr) {
            QObject::connect(model_, SIGNAL(DataChanged()), widget(), SLOT(update()));
            QObject::connect(model_, SIGNAL(PropertiesChanged()), widget(), SLOT(update()));
        }
    }
}
