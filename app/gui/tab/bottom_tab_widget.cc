//
// Created by wr on 2023/6/25.
//

#include "app/gui/tab/bottom_tab_widget.h"

namespace app {
    constexpr int kDefaultWidgetHeight = 256;
    BottomTabWidget::BottomTabWidget(QWidget* parent) :
            TabWidget(parent) {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        setMinimumHeight(kDefaultWidgetHeight);

    }
}
