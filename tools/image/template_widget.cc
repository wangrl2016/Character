//
// Created by wangrl2016 on 2023/8/30.
//

#include "tools/image/template_widget.h"
#include "tools/image/size_style.h"

namespace app {
    TemplateWidget::TemplateWidget(QWidget* parent) :
            QWidget(parent) {
        setFixedWidth(kLeftWidgetWidth);
        setAutoFillBackground(true);
    }
}
