//
// Created by wangrl2016 on 2023/8/28.
//

#include "tools/image/main_window.h"

namespace app {
    MainWindow::MainWindow() : QMainWindow() {
        setAcceptDrops(true);
    }

    void MainWindow::dragEnterEvent(QDragEnterEvent* event) {

    }

    void MainWindow::dropEvent(QDropEvent* event) {

    }
}
