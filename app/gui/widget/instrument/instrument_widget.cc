//
// Created by wangrl2016 on 2023/6/25.
//

#include <QHBoxLayout>
#include "app/gui/widget/instrument/instrument_widget.h"

namespace app {
    InstrumentWidget::InstrumentWidget(QWidget* parent) :
            QWidget(parent) {

        piano_roll_ = new PianoRoll(this);
        auto* layout = new QHBoxLayout(this);
        layout->addWidget(piano_roll_);
        setLayout(layout);
    }
}
