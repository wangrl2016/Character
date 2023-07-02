//
// Created by wangrl2016 on 2023/6/25.
//

#include <glog/logging.h>
#include <QVBoxLayout>
#include "app/gui/widget/instrument/instrument_widget.h"

namespace app {
    InstrumentWidget::InstrumentWidget(QWidget* parent) :
            QWidget(parent) {
        stacked_widget_ = new QStackedWidget(this);
        piano_roll_ = new PianoRoll(stacked_widget_);
        plucked_string_ = new PluckedString(stacked_widget_);
        stacked_widget_->addWidget(piano_roll_);
        stacked_widget_->addWidget(plucked_string_);
        stacked_widget_->setCurrentWidget(piano_roll_);

        middle_tool_bar_ = new MiddleToolBar(this);
        auto* layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        layout->addWidget(middle_tool_bar_);
        layout->addWidget(stacked_widget_);
        setLayout(layout);
    }

    void InstrumentWidget::CurrentInstrumentUpdate(int index) {
        LOG(INFO) << __FUNCTION__ << ", index " << index;
        stacked_widget_->setCurrentIndex(index);
    }
}
