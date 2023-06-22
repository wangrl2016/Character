//
// Created by wangrl2016 on 2023/6/21.
//

#include <QMenu>
#include <QMenuBar>
#include <QShortcut>
#include <QVBoxLayout>
#include "app/gui/dialog/about_dialog.h"
#include "app/gui/toolbar/top_tool_bar.h"
#include "main_window.h"

namespace app {
    MainWindow::MainWindow(QWidget* parent) :
            QMainWindow(parent) {
        SetupMenuBar();
        SetupToolBar();

        auto* central_widget = new QWidget(this);
        auto v_layout = new QVBoxLayout(central_widget);
        v_layout->setContentsMargins(0, 0, 0, 0);
        v_layout->setSpacing(0);

        timeline_widget_ = new TimelineWidget(central_widget);
        v_layout->addWidget(timeline_widget_);

        track_content_widget_ = new TrackContentWidget(central_widget);
        v_layout->addWidget(track_content_widget_);





        setCentralWidget(central_widget);
    }

    void MainWindow::SetupMenuBar() {
        // app menu
        auto* app_menu = new QMenu(this);
        menuBar()->addMenu(app_menu);

        // about
        auto* about_action = new QAction(QIcon(), tr("About Character"), app_menu);
        about_action->setMenuRole(QAction::ApplicationSpecificRole);
        connect(about_action, &QAction::triggered, this, [this]() {
           auto* dialog = new AboutDialog(this);
           dialog->show();
        });
        app_menu->addAction(about_action);

        // update
        auto* update_action = new QAction(QIcon(), tr("Check for Update"), app_menu);
        update_action->setMenuRole(QAction::ApplicationSpecificRole);
        connect(update_action, &QAction::triggered, this, [this]() {
            auto* dialog = new QDialog(this);
            dialog->show();
        });
        app_menu->addAction(update_action);

        // separator
        auto* separator = app_menu->addSeparator();
        separator->setMenuRole(QAction::ApplicationSpecificRole);

        // setting
        auto* setting_action = new QAction(QIcon(), tr("Setting"), app_menu);
        setting_action->setMenuRole(QAction::ApplicationSpecificRole);
        setting_action->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_0));
        connect(setting_action, &QAction::triggered, this, [this]() {
            auto* dialog = new QDialog(this);
            dialog->show();
        });
        app_menu->addAction(setting_action);

        // file menu
        auto* file_menu = new QMenu(this);
        menuBar()->addMenu(file_menu)->setText(tr("File"));

        // new
        auto* new_action = new QAction(QIcon(), tr("New"), file_menu);
        file_menu->addAction(new_action);
    }

    void MainWindow::SetupToolBar() {
#ifdef Q_OS_MACOS
        setUnifiedTitleAndToolBarOnMac(true);
#endif
        auto* top_tool_bar = new TopToolBar(this);
        addToolBar(top_tool_bar);

    }
}
