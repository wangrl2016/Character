//
// Created by wangrl2016 on 2023/9/10.
//

#include <QHBoxLayout>
#include "tools/image/layer_choice.h"

namespace app {
    LayerChoice::LayerChoice(QWidget* parent) :
            QWidget(parent) {
        auto* layout = new QHBoxLayout;
        layout->setSpacing(10);
        layout->setContentsMargins(0, 0, 0, 0);

        blend_mode_label_ = new QLabel(tr("混合"), this);
        blend_model_box_ = new QComboBox(this);
        transparency_label_ = new QLabel(tr("不透明度"), this);
        transparency_box_ = new QComboBox(this);

        layout->addWidget(blend_mode_label_);
        layout->addWidget(blend_model_box_);
        layout->addWidget(transparency_label_);
        layout->addWidget(transparency_box_);

        setLayout(layout);
    }
}
