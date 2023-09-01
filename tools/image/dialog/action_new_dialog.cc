//
// Created by wangrl2016 on 2023/8/29.
//

#include "tools/image/dialog/action_new_dialog.h"
#include "tools/image/size_style.h"

namespace app {
    ActionNewDialog::ActionNewDialog(QWidget* parent) : QDialog(parent) {
        setFixedSize(kDialogDefaultWidth, kDialogDefaultHeight);
    }
}
