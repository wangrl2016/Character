//
// Created by wr on 2023/6/22.
//

#include <QStandardItem>
#include "app/gui/widget/track_setting_widget.h"

namespace app {
    TrackSettingWidget::TrackSettingWidget(QWidget* parent) :
            QListView(parent) {;
        autoFillBackground();

        auto* standard_model = new QStandardItemModel(this);
        standard_model->appendRow(new QStandardItem("Banana"));
        standard_model->appendRow(new QStandardItem("Apple"));

        setModel(standard_model);
    }
}
