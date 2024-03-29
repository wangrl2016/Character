//
// Created by wangrl2016 on 2023/8/28.
//

#include <QAction>
#include <QImage>
#include <QMenu>
#include <QMenuBar>
#include <QHBoxLayout>

#include <QToolBar>
#include <glog/logging.h>
#include "tools/image/dialog/action_new_dialog.h"
#include "tools/image/main_window.h"
#include "tools/image/size_style.h"

namespace app {
    MainWindow::MainWindow() : QMainWindow() {
        // setAcceptDrops(true);

        SetupMenuBar();

        SetupToolBar();

        template_widget_ = new TemplateWidget(this);
        right_widget_ = new RightWidget(this);

        // scene
        cover_scene_ = new CoverGraphicsScene(this);
        cover_scene_->setSceneRect(0, 0, kProjectDefaultWidth, kProjectDefaultHeight);

        // view
        cover_view_ = new CoverGraphicsView(cover_scene_);
        cover_view_->setFixedSize(view_width_, view_height_);
        cover_view_->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        cover_view_->setStyleSheet("QWidget {"
                             "    border: none;"
                             "}");

        // layout
        auto* layout = new QHBoxLayout;
        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(template_widget_);
        layout->addWidget(cover_view_);
        layout->addWidget(right_widget_);

        auto* widget = new QWidget;
        widget->setLayout(layout);

        setCentralWidget(widget);

        setUnifiedTitleAndToolBarOnMac(true);
    }

    MainWindow::~MainWindow() {
        QImage image(kProjectDefaultWidth, kProjectDefaultHeight, QImage::Format_ARGB32);
        for (int i = 0; i < kProjectDefaultHeight; i++) {
            for (int j = 0; j < kProjectDefaultWidth; j++) {
                image.setPixel(j, i, 0xFFFFFFFF);
            }
        }
        QString path = "out.png";
        QPainter painter(&image);
        painter.setRenderHint(QPainter::Antialiasing);
        cover_scene_->render(&painter);
        image.save(path);
    }

//    void MainWindow::dragEnterEvent(QDragEnterEvent* event) {
//
//    }
//
//    void MainWindow::dropEvent(QDropEvent* event) {
//
//    }

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

        file_menu->addSeparator();

        // export action
        auto* export_action = new QAction(QIcon(), tr("Export"), file_menu);
        file_menu->addAction(export_action);
        connect(export_action, &QAction::triggered, this, [&]() {
            auto* dialog = new ActionNewDialog(this);
            dialog->show();
        });
    }

    void MainWindow::SetupToolBar() {
#ifdef Q_OS_MACOS
        setUnifiedTitleAndToolBarOnMac(true);
#endif
        auto* tool_bar = new QToolBar(this);
        tool_bar->setFixedHeight(32);
        addToolBar(tool_bar);
    }
}
