//
// Created by wr on 2023/6/22.
//

#include "app/gui/widget/track_setting_widget.h"

namespace app {
    TrackSettingWidget::TrackSettingWidget(QWidget* parent) :
            QWidget(parent) {
        setFixedWidth(256);
        autoFillBackground();
    }
}
