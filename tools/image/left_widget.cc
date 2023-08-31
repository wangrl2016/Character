//
// Created by admin on 2023/8/30.
//

#include "tools/image/left_widget.h"
#include "tools/image/size_style.h"

namespace app {
    LeftWidget::LeftWidget(QWidget* parent) :
            QWidget(parent) {
        setFixedWidth(kDefaultWidth / 4);
        setAutoFillBackground(true);
    }
}