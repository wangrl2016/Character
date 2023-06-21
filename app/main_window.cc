//
// Created by wangrl2016 on 2023/6/21.
//

#include <QMenu>
#include <QMenuBar>
#include "app/dialog/about_dialog.h"
#include "app/main_window.h"

namespace app {
    MainWindow::MainWindow(QWidget* parent) :
            QMainWindow(parent) {
        SetupMenuBar();
        SetupToolBar();
    }


    void MainWindow::SetupMenuBar() {
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
        connect(setting_action, &QAction::triggered, this, [this]() {
            auto* dialog = new QDialog(this);
            dialog->show();
        });
        app_menu->addAction(setting_action);
    }

    void MainWindow::SetupToolBar() {

    }
}
