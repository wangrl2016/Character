//
// Created by wangrl2016 on 2023/6/15.
//

#include "ui/view/setting/audio_device_selector.h"

namespace ui {
    AudioDeviceSelector::AudioDeviceSelector(QWidget* parent) :
            QWidget(parent) {
        output_device_combo_ = new QComboBox(this);
        output_device_combo_->addItem("One");
        output_device_combo_->addItem("Two");
        output_device_combo_->addItem("Three");

    }

    AudioDeviceSelector::~AudioDeviceSelector() = default;
}
