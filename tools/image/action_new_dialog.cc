//
// Created by wangrl2016 on 2023/8/29.
//

#include "tools/image/action_new_dialog.h"
#include "tools/image/size_style.h"

namespace app {
    ActionNewDialog::ActionNewDialog(QWidget* parent) : QDialog(parent) {
        setFixedSize(kDialogDefaultWidth, kDialogDefaultHeight);
        width_label_ = new QLabel(tr("Width"), this);
        width_label_->move(kSmallMargin, kSmallMargin);
        height_label_ = new QLabel(tr("Height"), this);
        height_label_->move(kSmallMargin, 2 * kSmallMargin + width_label_->height());
    }
}
