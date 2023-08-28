//
// Created by wangrl2016 on 2023/8/28.
//

#ifndef CHARACTER_MAIN_WINDOW_H
#define CHARACTER_MAIN_WINDOW_H

#include <QMainWindow>
#include <QDragEnterEvent>
#include <QDropEvent>

namespace app {
    class MainWindow : public QMainWindow {
    Q_OBJECT
    public:
        MainWindow();

        void dragEnterEvent(QDragEnterEvent* event) override;

        void dropEvent(QDropEvent* event);
    };
}


#endif //CHARACTER_MAIN_WINDOW_H
