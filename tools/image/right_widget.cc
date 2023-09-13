//
// Created by wangrl2016 on 2023/9/3.
//

#include <QVBoxLayout>
#include <QLabel>
#include "tools/image/right_widget.h"
#include "tools/image/size_style.h"

namespace app {
    RightWidget::RightWidget(QWidget* parent) :
            QWidget(parent) {
        setFixedWidth(kRightWidgetWidth);

        layer_label_ = new LayerLabel(this);
        layer_widget_ = new LayerWidget(this);
        layer_choice_ = new LayerChoice(this);
        property_widget_ = new PropertyWidget(this);

        auto* layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        layout->addWidget(layer_label_);
        layout->addWidget(layer_widget_);
        layout->addWidget(layer_choice_);
        layout->addWidget(property_widget_);

        setLayout(layout);
    }


}