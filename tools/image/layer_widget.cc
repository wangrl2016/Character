//
// Created by wangrl2016 on 2023/9/1.
//

#include <QHBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include "tools/image/layer_widget.h"
#include "tools/image/size_style.h"

namespace app {
    LayerWidget::LayerWidget(QWidget* parent) :
            QListWidget(parent) {
        setFixedWidth(kRightWidgetWidth);
        setAutoFillBackground(true);

        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(10, 100));
        addItem(item);

        QWidget* w = new QWidget;
        QHBoxLayout* layout = new QHBoxLayout;
        QPushButton* push_button = new QPushButton(w);
        QCheckBox* check_box = new QCheckBox(w);
        layout->addWidget(check_box);
        layout->addWidget(push_button);
        w->setLayout(layout);

        setItemWidget(item, w);
    }
}
