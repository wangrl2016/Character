//
// Created by wr on 2023/9/9.
//

#include "tools/image/layer_button.h"

namespace app {
    LayerButton::LayerButton(QWidget* parent) :
            QPushButton(parent) {
        setFixedSize(32, 32);
        setIconSize({24, 24});
        // setToolTip(tr("添加新图层"));
        setStyleSheet("QPushButton {"
                      "    border: none;"
                      // "    background-color: yellow;"
                      "    border-radius: 4px;"
                      "}"
                      "QPushButton:pressed {"
                      "    background-color: #DCDCDC;"
                      "}"
                      "QPushButton:hover:!pressed {"
                      "    background-color: #F0F0F0;"
                      "}");
    }
}