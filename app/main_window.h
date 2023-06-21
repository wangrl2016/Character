//
// Created by wangrl2016 on 2023/6/21.
//

#ifndef CHARACTER_MAIN_WINDOW_H
#define CHARACTER_MAIN_WINDOW_H

#include <QMainWindow>

namespace app {
    class MainWindow : public QMainWindow {
    Q_OBJECT
    public:
        explicit MainWindow(QWidget* parent = nullptr);

    private:
        void SetupMenuBar();

        void SetupToolBar();

    };
}


#endif //CHARACTER_MAIN_WINDOW_H
