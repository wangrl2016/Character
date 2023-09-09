//
// Created by wangrl2016 on 2023/8/31.
//

#include "tools/image/property_widget.h"
#include "tools/image/size_style.h"

namespace app {
    PropertyWidget::PropertyWidget(QWidget* parent) :
            QWidget(parent) {
        setFixedWidth(kRightWidgetWidth);
        setFixedHeight(50);
        // setAutoFillBackground(true);

        setStyleSheet("QWidget {"
                      "    background-color: black;"
                      "}");
        setAutoFillBackground(true);
    }
}
