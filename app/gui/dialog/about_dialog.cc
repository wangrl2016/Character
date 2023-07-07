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
        version_label_->setText(ConfigManager::ProjectName() + " version: " + ConfigManager::DefaultVersion());

        copyright_label_ = new QLabel(this);
        copyright_label_->setText("Copyright © 2023-2023 <wangrl2016@gmail.com>");

        layout->addWidget(version_label_);
        layout->addWidget(copyright_label_);
        setLayout(layout);
    }
}
