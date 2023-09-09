//
// Created by wangrl2016 on 2023/9/9.
//

#include <QVBoxLayout>
#include "tools/image/layer_label.h"
#include "tools/image/size_style.h"

namespace app {
    constexpr int kDefaultLabelHeight = 120;

    LayerLabel::LayerLabel(QWidget* parent) :
            QWidget(parent) {
        // setFixedWidth(kRightWidgetWidth);
        setFixedWidth(kRightWidgetWidth);
        setFixedHeight(kDefaultLabelHeight);
        setStyleSheet("QWidget {"
                      "    background-color: white;"
                      "}");
        setAttribute(Qt::WA_StyledBackground);

        layer_label_ = new QLabel(this);
        QFont font;
        font.setPixelSize(16);
        font.setBold(true);
        layer_label_->setFont(font);
        layer_label_->setText(tr("图层"));

        layer_tool_ = new LayerTool(this);

        auto* layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        layout->addWidget(layer_label_);
        layout->addWidget(layer_tool_);

        setLayout(layout);
    }
}