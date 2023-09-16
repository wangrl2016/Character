//
// Created by wr on 2023/9/9.
//

#ifndef CHARACTER_LAYER_LABEL_H
#define CHARACTER_LAYER_LABEL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "layer_tool.h"
#include "layer_choice.h"

namespace app {
    class LayerLabel : public QWidget {
    Q_OBJECT
    public:
        LayerLabel(QWidget* parent = nullptr);

    private:
        QLabel* layer_label_;
        LayerTool* layer_tool_;
        LayerChoice* layer_choice_;
    };
}

#endif //CHARACTER_LAYER_LABEL_H
