//
// Created by admin on 2023/6/16.
//

#include <QHBoxLayout>
#include "ui/view/setting/setting_widget.h"
#include "ui/view/setting/audio_device_selector.h"

namespace ui {
    SettingWidget::SettingWidget(QWidget* parent) {
        auto* main_layout = new QHBoxLayout(this);
        main_layout->addWidget(new AudioDeviceSelector);
    }

    SettingWidget::~SettingWidget() = default;
}