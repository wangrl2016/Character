//
// Created by wangrl2016 on 2023/6/21.
//

#include <QVBoxLayout>
#include "app/gui/dialog/about_dialog.h"
#include "app/config/config_manager.h"

namespace app {
    AboutDialog::AboutDialog(QWidget* parent) :
            QDialog(parent) {
        setWindowFlag(Qt::WindowStaysOnTopHint, true);

        auto* layout = new QVBoxLayout(this);

        version_label_ = new QLabel(this);
        version_label_->setText(ConfigManager::DefaultVersion());

        layout->addWidget(version_label_);
        setLayout(layout);
    }
}
