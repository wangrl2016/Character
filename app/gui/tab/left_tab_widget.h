//
// Created by wangrl2016 on 2023/6/24.
//

#ifndef CHARACTER_LEFT_TAB_WIDGET_H
#define CHARACTER_LEFT_TAB_WIDGET_H

#include "app/gui/tab/tab_widget.h"

namespace app {
    class LeftTabWidget : public TabWidget {
    Q_OBJECT
    public:
        LeftTabWidget(QWidget* parent = nullptr);
    };
}

#endif //CHARACTER_LEFT_TAB_WIDGET_H
