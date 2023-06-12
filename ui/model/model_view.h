//
// Created by wangrl2016 on 2023/6/12.
//

#ifndef CHARACTER_MODEL_VIEW_H
#define CHARACTER_MODEL_VIEW_H

#include <QWidget>
#include "ui/model/model.h"
#include "ui/model/model_view.h"

namespace ui {
    class ModelView {
    public:
        ModelView(std::shared_ptr<Model> model,
                  std::shared_ptr<QWidget> widget);

        virtual ~ModelView();

        virtual void SetModel(std::shared_ptr<Model> model,
                              bool is_old_model_valid = true);

        virtual void UnsetModel();

        std::shared_ptr<Model> model() { return model_; }

    protected:
        // subclasses can re-implement this to track model-changes
        virtual void ModelChanged() {

        }

        std::shared_ptr<QWidget> widget() { return widget_; }

        virtual void DoConnections();

    private:
        std::shared_ptr<QWidget> widget_;
        std::shared_ptr<Model> model_;
    };
}

#endif //CHARACTER_MODEL_VIEW_H
