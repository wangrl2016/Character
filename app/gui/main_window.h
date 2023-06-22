//
// Created by wangrl2016 on 2023/6/21.
//

#ifndef CHARACTER_MAIN_WINDOW_H
#define CHARACTER_MAIN_WINDOW_H

#include <QMainWindow>
#include "app/gui/widget/timeline_widget.h"

namespace app {
    class MainWindow : public QMainWindow {
    Q_OBJECT
    public:
        explicit MainWindow(QWidget* parent = nullptr);

    private:
        void SetupMenuBar();

        void SetupToolBar();

    private:
        TimelineWidget* timeline_widget_;

        double current_play_time_;
    };
}


#endif //CHARACTER_MAIN_WINDOW_H
