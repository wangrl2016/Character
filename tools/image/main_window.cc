//
// Created by wangrl2016 on 2023/8/28.
//

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QHBoxLayout>
#include "tools/image/action_new_dialog.h"
#include "tools/image/main_window.h"
#include "tools/image/size_style.h"

namespace app {
    MainWindow::MainWindow() : QMainWindow() {
        setAcceptDrops(true);

        SetupMenuBar();

        left_widget_ = new LeftWidget(this);
        right_widget_ = new RightWidget(this);

        // scene
        scene_ = new CoverGraphicsScene(this);
        scene_->setSceneRect(0, 0, kProjectDefaultWidth, kProjectProjectHeight);

        // view
        view_ = new CoverGraphicsView(scene_);
        view_->setFixedSize(kProjectDefaultWidth, kProjectProjectHeight);
        view_->setStyleSheet("QWidget {"
                             "    border: none;"
                             "}");

        // layout
        auto* layout = new QHBoxLayout;
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(left_widget_);
        layout->addWidget(view_);
        layout->addWidget(right_widget_);

        auto* widget = new QWidget;
        widget->setLayout(layout);

        setCentralWidget(widget);

        setUnifiedTitleAndToolBarOnMac(true);
    }

    void MainWindow::dragEnterEvent(QDragEnterEvent* event) {

    }

    void MainWindow::dropEvent(QDropEvent* event) {

    }

    void MainWindow::mousePressEvent(QMouseEvent* event) {

    }

    void MainWindow::mouseMoveEvent(QMouseEvent* event) {

    }

    void MainWindow::mouseReleaseEvent(QMouseEvent* event) {

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
