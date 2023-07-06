//
// Created by wangrl2016 on 2023/6/26.
//

#include <glog/logging.h>
#include "app/gui/toolbar/middle_tool_bar.h"
#include "app/gui/widget/instrument/instrument_widget.h"

namespace app {
    constexpr int kToolBarFixedHeight = 24;

    MiddleToolBar::MiddleToolBar(QWidget* parent) :
            QToolBar(parent) {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        setFixedHeight(kToolBarFixedHeight);
        setMovable(false);
        setStyleSheet("QToolBar {"
                      "    border: none;"
                      "}");

        instrument_combo_box_ = new QComboBox(this);
        instrument_combo_box_->addItem(tr("Piano"));
        instrument_combo_box_->addItem(tr("String"));
        instrument_combo_box_->addItem(tr("Drum"));
        addWidget(instrument_combo_box_);

        setting_action_ = new QAction(QIcon(":icon/setting"),
                                      tr("Setting"),
                                      this);
        addAction(setting_action_);

        connect(instrument_combo_box_,
                SIGNAL(currentIndexChanged(int)),
                parent,
                SLOT(CurrentInstrumentUpdate(int)));
    }
}
