//
// Created by wr on 2023/6/15.
//

#ifndef CHARACTER_DEVICE_COMBO_BOX_H
#define CHARACTER_DEVICE_COMBO_BOX_H

#include <QComboBox>

namespace ui {
    class DeviceComboBox : public QComboBox {
    public:
        explicit DeviceComboBox(QWidget* parent = nullptr);

        ~DeviceComboBox();
    };
}

#endif //CHARACTER_DEVICE_COMBO_BOX_H
