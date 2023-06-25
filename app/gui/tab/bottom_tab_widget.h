//
// Created by wr on 2023/6/25.
//

#ifndef CHARACTER_BOTTOM_TAB_WIDGET_H
#define CHARACTER_BOTTOM_TAB_WIDGET_H

#include "app/gui/tab/tab_widget.h"

namespace app {
    class BottomTabWidget : public TabWidget {
    Q_OBJECT
    public:
        explicit BottomTabWidget(QWidget* parent = nullptr);
    };
}

#endif //CHARACTER_BOTTOM_TAB_WIDGET_H
