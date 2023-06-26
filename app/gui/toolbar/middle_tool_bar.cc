//
// Created by wangrl2016 on 2023/6/26.
//

#include "app/gui/toolbar/middle_tool_bar.h"

namespace app {
    constexpr int kToolBarFixedHeight = 24;

    MiddleToolBar::MiddleToolBar(QWidget* parent) :
            QToolBar(parent) {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        setFixedHeight(kToolBarFixedHeight);
        setMovable(false);
        setStyleSheet("QToolBar {"
                      "    border: none;"
                      "    margin-top: 3px;"
                      "    margin-bottom: 3px;"
                      "}");

        setting_action_ = new QAction(QIcon(":icon/setting"),
                                      tr("Setting"),
                                      this);
        addAction(setting_action_);
    }
}