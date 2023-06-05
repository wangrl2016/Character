//
// Created by wangrl2016 on 2023/6/2.
//

#include <QFileDialog>
#include <QMenuBar>
#include <QMdiSubWindow>
#include <glog/logging.h>
#include <QTextEdit>
#include "view/widgets/character_window.h"
#include "view/widgets/waveform_widget.h"

namespace view {
    CharacterWindow::CharacterWindow() {
        waveform_widget_ = new WaveformWidget(this);
        setCentralWidget(waveform_widget_);
        // setUnifiedTitleAndToolBarOnMac(true);
        CreateActions();
        CreateMenus();
    }

    CharacterWindow::~CharacterWindow() {

    }

    bool CharacterWindow::NewFile() {
        return true;
    }

    bool CharacterWindow::OpenFile() {
        auto file_path = QFileDialog::getOpenFileName(this,
                                                      tr("Open"),
                                                      QString(),
                                                      QString());
        if (file_path.isNull() || file_path.isEmpty())
            return false;

        LOG(INFO) << __FUNCTION__ << ", path " << file_path.toStdString();
        waveform_widget_->LoadAudio(file_path);
        return true;
    }

    void CharacterWindow::CreateActions() {
        file_new_action_ = new QAction(tr("&New"), this);
        file_new_action_->setShortcuts(QKeySequence::New);
        file_new_action_->setStatusTip(tr("Create a new file"));
        connect(file_new_action_, &QAction::triggered, this, &CharacterWindow::NewFile);

        file_open_action_ = new QAction(tr("&Open"), this);
        file_open_action_->setShortcuts(QKeySequence::Open);
        file_open_action_->setStatusTip(tr("Open a file"));
        connect(file_open_action_, &QAction::triggered, this, &CharacterWindow::OpenFile);
    }

    void CharacterWindow::CreateMenus() {
        auto file_menu = menuBar()->addMenu(tr("&File"));
        file_menu->addAction(file_new_action_);
        file_menu->addAction(file_open_action_);

    }
}
