//
// Created by wangrl2016 on 2023/8/28.
//

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include "tools/image/action_new_dialog.h"
#include "tools/image/main_window.h"

namespace app {
    MainWindow::MainWindow() : QMainWindow() {
        setAcceptDrops(true);

        SetupMenuBar();
    }

    void MainWindow::dragEnterEvent(QDragEnterEvent* event) {

    }

    void MainWindow::dropEvent(QDropEvent* event) {

    }

    void MainWindow::SetupMenuBar() {
        // file menu
        auto* file_menu = new QMenu(this);
        menuBar()->addMenu(file_menu)->setText(tr("File"));

        // new action
        auto* new_action = new QAction(QIcon(), tr("New"), file_menu);
        new_action->setShortcut(QKeySequence::New);
        file_menu->addAction(new_action);
        connect(new_action, &QAction::triggered, this, [&]() {
            auto* dialog = new ActionNewDialog(this);
            dialog->show();
        });

        // open action
        auto* open_action = new QAction(QIcon(), tr("Open"), file_menu);
        open_action->setShortcut(QKeySequence::Open);
        file_menu->addAction(open_action);
    }
}
