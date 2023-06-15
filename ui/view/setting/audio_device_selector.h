//
// Created by wangrl2016 on 2023/6/15.
//

#ifndef CHARACTER_AUDIO_DEVICE_SELECTOR_H
#define CHARACTER_AUDIO_DEVICE_SELECTOR_H

#include <QComboBox>
#include <QWidget>

namespace ui {
    class AudioDeviceSelector : public QWidget {
    Q_OBJECT
    public:
        AudioDeviceSelector(QWidget* parent = nullptr);

        ~AudioDeviceSelector();

    private:
        QComboBox* device_types_combo_;
        QComboBox* output_device_combo_;
    };
}


#endif //CHARACTER_AUDIO_DEVICE_SELECTOR_H
