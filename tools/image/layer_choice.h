//
// Created by wangrl2016 on 2023/9/10.
//

#ifndef CHARACTER_LAYER_CHOICE_H
#define CHARACTER_LAYER_CHOICE_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>

namespace app {
    class LayerChoice : public QWidget {
    public:
        LayerChoice(QWidget* parent = nullptr);

    private:
        QLabel* blend_mode_label_;
        QComboBox* blend_model_box_;
        QLabel* transparency_label_;
        QComboBox* transparency_box_;
    };
}

#endif //CHARACTER_LAYER_CHOICE_H
