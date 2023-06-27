//
// Created by wangrl2016 on 2023/6/27.
//

#ifndef CHARACTER_STATUS_BAR_H
#define CHARACTER_STATUS_BAR_H

#include <QStatusBar>

namespace app {
    class StatusBar : public QStatusBar {
    Q_OBJECT
    public:
        explicit StatusBar(QWidget* parent = nullptr);
    };
}

#endif //CHARACTER_STATUS_BAR_H
