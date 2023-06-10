//
// Created by wangrl2016 on 2023/6/2.
//

#include <QDockWidget>
#include <QFileDialog>
#include <QMenuBar>
#include <QTextEdit>
#include <QToolBar>
#include <glog/logging.h>
#include "module/audio_graph/audio_bridge.h"
#include "view/widgets/main_window.h"
#include "view/widgets/waveform_widget.h"

namespace view {
    MainWindow::MainWindow() {
        waveform_widget_ = new WaveformWidget(this);
        setCentralWidget(waveform_widget_);
        // setUnifiedTitleAndToolBarOnMac(true);
        CreateActions();
        CreateMenus();

        CreateToolBar();

        CreateDockWindows();

        audio_graph::AudioBridge::Create();

        audio_graph::AudioBridge::Start();
    }

    MainWindow::~MainWindow() {
        audio_graph::AudioBridge::Stop();
        audio_graph::AudioBridge::Destroy();
    }

    bool MainWindow::NewFile() {
        return true;
    }

    bool MainWindow::OpenFile() {
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

    void MainWindow::Play() {
        LOG(INFO) << __FUNCTION__;
        is_playing_ = true;
        play_action_->setEnabled(true);
        pause_action_->setEnabled(false);
    }

    void MainWindow::Pause() {
        LOG(INFO) << __FUNCTION__;
        is_playing_ = false;
        play_action_->setEnabled(false);
        pause_action_->setEnabled(true);
    }

    void MainWindow::PlayOrPause() {
        is_playing_ = !is_playing_;
        LOG(INFO) << __FUNCTION__ << " " << is_playing_;
        if (is_playing_) {
            play_or_pause_button_->setIcon(QIcon(":toolbar/pause"));
            audio_graph::AudioBridge::StartBeat();
        } else {
            play_or_pause_button_->setIcon(QIcon(":toolbar/play_arrow"));
            audio_graph::AudioBridge::StopBeat();
        }
    }

    void MainWindow::Stop() {

    }

    void MainWindow::CreateActions() {
        file_new_action_ = new QAction(tr("&New"), this);
        file_new_action_->setShortcuts(QKeySequence::New);
        file_new_action_->setStatusTip(tr("Create a new file"));
        connect(file_new_action_, &QAction::triggered, this, &MainWindow::NewFile);

        file_open_action_ = new QAction(tr("&Open"), this);
        file_open_action_->setShortcuts(QKeySequence::Open);
        file_open_action_->setStatusTip(tr("Open a file"));
        connect(file_open_action_, &QAction::triggered, this, &MainWindow::OpenFile);


    }

    void MainWindow::CreateMenus() {
        auto file_menu = menuBar()->addMenu(tr("&File"));
        file_menu->addAction(file_new_action_);
        file_menu->addAction(file_open_action_);

    }

    void MainWindow::CreateToolBar() {
        tool_bar_ = new QToolBar(this);

        play_or_pause_button_ = new QPushButton;
        play_or_pause_button_->setIcon(QIcon(":toolbar/play_arrow"));
        connect(play_or_pause_button_, &QPushButton::clicked,
                this, &MainWindow::PlayOrPause);


        play_action_ = new QAction(QIcon(":toolbar/play_arrow"), tr("Play"), this);
        connect(play_action_, &QAction::triggered, this, &MainWindow::Play);
        play_action_->setShortcut(Qt::Key_Space);
        play_action_->setEnabled(true);

        pause_action_ = new QAction(QIcon(":toolbar/pause"), tr("Pause"), this);
        connect(pause_action_, &QAction::triggered, this, &MainWindow::Pause);
        pause_action_->setShortcut(Qt::Key_Space);
        play_action_->setEnabled(false);

        stop_action_ = new QAction(QIcon(":toolbar/stop"), tr("Stop"), this);
        connect(stop_action_, &QAction::triggered, this, &MainWindow::Stop);
        play_action_->setEnabled(false);

        tool_bar_->addWidget(play_or_pause_button_);
        tool_bar_->addAction(play_action_);
        tool_bar_->addAction(pause_action_);
        tool_bar_->addAction(stop_action_);
        addToolBar(tool_bar_);
    }

    void MainWindow::CreateDockWindows() {
        auto* dock = new QDockWidget(tr("Customers"), this);
        dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

        addDockWidget(Qt::RightDockWidgetArea, dock);

    }
}
