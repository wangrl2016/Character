//
// Created by wangrl2016 on 2023/6/15.
//

#include <QVBoxLayout>
#include "ui/view/setting/audio_device_selector.h"
#include "ui/view/setting/device_combo_box.h"

namespace ui {
    AudioDeviceSelector::AudioDeviceSelector(QWidget* parent) :
            QWidget(parent) {

        auto* v_layout = new QVBoxLayout(this);

        device_types_combo_ = new DeviceComboBox(this);


        output_device_combo_ = new DeviceComboBox(this);
        output_device_combo_->addItem("One");
        output_device_combo_->addItem("Two");
        output_device_combo_->addItem("Three");

        v_layout->addWidget(device_types_combo_);
        v_layout->addWidget(output_device_combo_);

    }

    AudioDeviceSelector::~AudioDeviceSelector() = default;
}
