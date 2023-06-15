//
// Created by wr on 2023/6/15.
//

#include "ui/view/setting/device_combo_box.h"

namespace ui {
    const QString kDeviceStyle = R"(
        QComboBox {
            border: 1px solid gray;
            border-radius: 3px;
            padding: 1px 18px 1px 3px;
            min-width: 6em;
        }
        QComboBox:on { /* shift the text when the popup opens */
            padding-top: 3px;
            padding-left: 4px;
        }

        QComboBox::drop-down {
            subcontrol-origin: padding;
            subcontrol-position: top right;
            width: 15px;

            border-left-width: 1px;
            border-left-color: darkgray;
            border-left-style: solid; /* just a single line */
            border-top-right-radius: 3px; /* same radius as the QComboBox */
            border-bottom-right-radius: 3px;
        }

        # QComboBox::down-arrow {
        #     image: url(/usr/share/icons/crystalsvg/16x16/actions/1downarrow.png);
        # }

        QComboBox::down-arrow:on { /* shift the arrow when popup is open */
            top: 1px;
            left: 1px;
        }
    )";

    DeviceComboBox::DeviceComboBox(QWidget* parent) :
            QComboBox(parent) {
        setStyleSheet(kDeviceStyle);
    }

    DeviceComboBox::~DeviceComboBox() = default;
}
