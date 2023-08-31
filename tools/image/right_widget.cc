//
// Created by wangrl2016 on 2023/8/31.
//

#include "tools/image/right_widget.h"
#include "tools/image/size_style.h"

namespace app {
    RightWidget::RightWidget(QWidget* parent) :
            QWidget(parent) {
        setFixedWidth(kDefaultWidth / 4);
        setAutoFillBackground(true);
    }
}
