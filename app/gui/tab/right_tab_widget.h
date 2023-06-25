//
// Created by wangrl2016 on 2023/6/26.
//

#ifndef CHARACTER_RIGHT_TAB_WIDGET_H
#define CHARACTER_RIGHT_TAB_WIDGET_H

#include "tab_widget.h"

namespace app {
    class RightTabWidget : public TabWidget {
    Q_OBJECT
    public:
        RightTabWidget(QWidget* parent = nullptr);
    };
}



#endif //CHARACTER_RIGHT_TAB_WIDGET_H
