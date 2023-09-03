//
// Created by wangrl2016 on 2023/9/3.
//

#include <QVBoxLayout>
#include "tools/image/right_widget.h"
#include "tools/image/size_style.h"

namespace app {
    RightWidget::RightWidget(QWidget* parent) :
            QWidget(parent) {

        setFixedWidth(kRightWidgetWidth);

        layer_widget_ = new LayerWidget(this);
        property_widget_ = new PropertyWidget(this);

        auto* layout = new QVBoxLayout(this);
        layout->addWidget(layer_widget_);
        layout->addWidget(property_widget_);

        setLayout(layout);
    }


}