//
// Created by wangrl2016 on 2023/6/15.
//

#include <QFormLayout>
#include <QLabel>
#include "module/audio_graph/audio_bridge.h"
#include "ui/view/setting/audio_device_selector.h"
#include "ui/view/setting/device_combo_box.h"

namespace ui {
    AudioDeviceSelector::AudioDeviceSelector(QWidget* parent) :
            QWidget(parent) {

        // When you use a layout, you do not need to pass a parent when
        // constructing the child widgets. The layout will automatically re-parent the widgets.
        auto* main_layout = new QFormLayout(this);

        auto* device_type_label = new QLabel(tr("设备驱动"));
        auto* device_type_combo = new DeviceComboBox;
        int current_device_type_index = -1;
        auto device_types = audio_graph::AudioBridge::DeviceTypes(&current_device_type_index);
        for (auto& type : device_types) {
            device_type_combo->addItem(QString(type.c_str()));
        }

        auto* input_device_label = new QLabel(tr("输入设备"));
        auto* input_device_combo = new DeviceComboBox;
        int current_input_device_index = -1;
        auto input_device_names = audio_graph::AudioBridge::InputDeviceNames(&current_input_device_index);
        for (auto& name : input_device_names) {
            input_device_combo->addItem(QString(name.c_str()));
        }

        auto* output_device_label = new QLabel(tr("输出设备"));
        auto* output_device_combo = new DeviceComboBox;
        int current_output_device_index = -1;
        auto output_device_names = audio_graph::AudioBridge::OutputDeviceNames(&current_output_device_index);
        for (auto& name : output_device_names) {
            output_device_combo->addItem(QString(name.c_str()));
        }

        auto* sample_rate_label = new QLabel(tr("采样率"));
        auto* sample_rate_combo = new DeviceComboBox;
        int current_sample_rate_index = -1;
        auto sample_rates = audio_graph::AudioBridge::SampleRates(&current_sample_rate_index);
        for (auto& sample_rate : sample_rates) {
            sample_rate_combo->addItem(QString::number(sample_rate));
        }

        auto* buffer_size_label = new QLabel(tr("缓冲区"));
        auto* buffer_size_combo = new DeviceComboBox;
        int current_buffer_size_index = -1;
        auto buffer_sizes = audio_graph::AudioBridge::BufferSizes(&current_buffer_size_index);
        for (auto& buffer_size : buffer_sizes) {
            // TODO: Remove some unused item
            buffer_size_combo->addItem(QString::number(buffer_size));
        }

        main_layout->addRow(device_type_label, device_type_combo);
        main_layout->addRow(input_device_label, input_device_combo);
        main_layout->addRow(output_device_label, output_device_combo);
        main_layout->addRow(sample_rate_label, sample_rate_combo);
        main_layout->addRow(buffer_size_label, buffer_size_combo);

        output_device_combo_ = new QComboBox;
        output_device_combo_->addItem("One");
        output_device_combo_->addItem("Two");
        output_device_combo_->addItem("Three");

        main_layout->addWidget(output_device_combo_);

        setLayout(main_layout);
    }

    AudioDeviceSelector::~AudioDeviceSelector() = default;
}
