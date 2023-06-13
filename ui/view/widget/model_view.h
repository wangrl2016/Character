//
// Created by wangrl2016 on 2023/6/12.
//

#ifndef CHARACTER_MODEL_VIEW_H
#define CHARACTER_MODEL_VIEW_H

#include <QWidget>
#include "ui/model/model.h"
#include "ui/view/widget/model_view.h"

namespace ui {
    class ModelView {
    public:
        ModelView(Model* model, QWidget* widget);

        virtual ~ModelView();

        virtual void SetModel(Model* model, bool is_old_model_valid = true);

        virtual void UnsetModel();

        Model* model() { return model_; }

        template<class T>
        T* CastModel() {
            return dynamic_cast<T*>(model());
        }

    protected:
        // subclasses can re-implement this to track model-changes
        virtual void ModelChanged() {}

        QWidget* widget() { return widget_; }

        virtual void DoConnections();

    private:
        QWidget* widget_;
        Model* model_;
    };
}

#endif //CHARACTER_MODEL_VIEW_H
