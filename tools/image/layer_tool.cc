//
// Created by wr on 2023/9/9.
//

#include <QHBoxLayout>
#include "tools/image/layer_tool.h"
#include "tools/image/layer_button.h"

namespace app {
    LayerTool::LayerTool(QWidget* parent) :
            QWidget(parent) {
        add_layer_btn_ = new LayerButton(this);
        add_layer_btn_->setIcon(QIcon(":layer/add_layer"));
        adjust_layer_btn_ = new LayerButton(this);
        adjust_layer_btn_->setIcon(QIcon(":layer/adjust_layer"));
        effect_layer_btn_ = new LayerButton(this);
        effect_layer_btn_->setIcon(QIcon(":layer/layer_effect"));
        mask_layer_btn_ = new LayerButton(this);
        mask_layer_btn_->setIcon(QIcon(":layer/layer_mask"));
        cut_mask_layer_btn_ = new LayerButton(this);
        cut_mask_layer_btn_->setIcon(QIcon(":layer/layer_copy"));
        arrange_layer_btn_ = new LayerButton(this);
        arrange_layer_btn_->setIcon(QIcon(":layer/layer_arrange"));
        delete_layer_btn_ = new LayerButton(this);
        delete_layer_btn_->setIcon(QIcon(":layer/layer_delete"));

        auto* layout = new QHBoxLayout(this);
        layout->setContentsMargins(0, 10, 0, 0);
        layout->addWidget(add_layer_btn_);
        layout->addWidget(adjust_layer_btn_);
        layout->addWidget(effect_layer_btn_);
        layout->addWidget(mask_layer_btn_);
        layout->addWidget(cut_mask_layer_btn_);
        layout->addWidget(arrange_layer_btn_);
        layout->addWidget(delete_layer_btn_);

        setLayout(layout);

    }
}
