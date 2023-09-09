//
// Created by wr on 2023/9/9.
//

#ifndef CHARACTER_LAYER_BUTTON_H
#define CHARACTER_LAYER_BUTTON_H

#include <QPushButton>
#include <QWidget>

namespace app {
    class LayerButton : public QPushButton {
        Q_OBJECT
    public:
        LayerButton(QWidget* parent = nullptr);
    };
}


#endif //CHARACTER_LAYER_BUTTON_H
