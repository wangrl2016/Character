//
// Created by wangrl2016 on 2023/7/13.
//

#include <QVBoxLayout>
#include <QPushButton>
#include "app/gui/dialog/export_dialog.h"

namespace app {
    ExportDialog::ExportDialog(QWidget* parent) :
            QDialog(parent) {
        setAttribute(Qt::WA_DeleteOnClose);

        auto* layout = new QVBoxLayout(this);
        export_button_ = new QPushButton(this);
        layout->addWidget(export_button_);

        setLayout(layout);
    }

    ExportDialog::~ExportDialog() {

    }
}
