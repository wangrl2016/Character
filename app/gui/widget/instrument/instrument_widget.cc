//
// Created by wangrl2016 on 2023/6/25.
//

#include <QVBoxLayout>
#include "app/gui/widget/instrument/instrument_widget.h"

namespace app {
    InstrumentWidget::InstrumentWidget(QWidget* parent) :
            QWidget(parent) {

        piano_roll_ = new PianoRoll(this);
        middle_tool_bar_ = new MiddleToolBar(this);
        auto* layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        layout->addWidget(middle_tool_bar_);
        layout->addWidget(piano_roll_);
        setLayout(layout);
    }
}
