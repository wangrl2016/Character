//
// Created by wr on 2023/6/24.
//

#ifndef CHARACTER_TAB_WIDGET_H
#define CHARACTER_TAB_WIDGET_H

#include <QTabWidget>

namespace app {
    class TabWidget : public QTabWidget {
        Q_OBJECT
    public:
        TabWidget(QWidget* parent = nullptr);
    };
}


#endif //CHARACTER_TAB_WIDGET_H
