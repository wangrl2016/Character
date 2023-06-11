//
// Created by wangrl2016 on 2023/6/2.
//

#include <QDockWidget>
#include <QFileDialog>
#include <QMenuBar>
#include <QTextEdit>
#include <QToolBar>
#include <glog/logging.h>
#include <QHBoxLayout>
#include "module/audio_graph/audio_bridge.h"
#include "main_window.h"
#include "waveform_widget.h"

namespace ui {
    MainWindow::MainWindow() {
        //waveform_widget_ = new WaveformWidget(this);


        QWidget* widget = new QWidget(this);
        QVBoxLayout* v_layout = new QVBoxLayout(widget);
        // widget->setLayout(v_layout);

        QWidget* h_widget = new QWidget(widget);
        QHBoxLayout* h_layout = new QHBoxLayout(h_widget);
        // h_widget->setLayout(h_layout);
        central_widget_ = new QWidget(h_widget);
        central_widget_->setFixedSize(600, 400);

        // setUnifiedTitleAndToolBarOnMac(true);
        CreateActions();
        CreateMenus();

        CreateToolBar();

        // CreateDockWindows();

        left_tab_widget_ = new QTabWidget(h_widget);
        right_tab_widget_ = new QTabWidget(h_widget);
        down_tab_widget_ = new QTabWidget(widget);

        left_tab_widget_->setTabPosition(QTabWidget::West);
        right_tab_widget_->setTabPosition(QTabWidget::East);
        down_tab_widget_->setTabPosition(QTabWidget::South);

        left_tab_widget_->addTab(new QWidget(), "TAB 1");
        left_tab_widget_->addTab(new QWidget(), "TAB 2");
        right_tab_widget_->addTab(new QWidget(), "TAB 1");
        right_tab_widget_->addTab(new QWidget(), "TAB 2");

        piano_view_ = new PianoView(down_tab_widget_);
        down_tab_widget_->addTab(piano_view_, tr("Piano"));
        down_tab_widget_->addTab(new QWidget(), "TAB 2");


        h_layout->addWidget(left_tab_widget_);
        // h_layout->addWidget(waveform_widget_);
        h_layout->addWidget(central_widget_);
        h_layout->addWidget(right_tab_widget_);



        v_layout->addWidget(h_widget);
        v_layout->addWidget(down_tab_widget_);

        setCentralWidget(widget);


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
            play_or_pause_button_->setIcon(pause_icon_);
            audio_graph::AudioBridge::StartBeat();
        } else {
            play_or_pause_button_->setIcon(play_icon_);
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

        play_icon_ = QIcon(":toolbar/play_arrow");
        pause_icon_ = QIcon(":toolbar/pause");

        play_or_pause_button_ = new QPushButton(this);
        play_or_pause_button_->setIcon(play_icon_);
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
        // auto* dock = new QDockWidget(tr("Customers"), this);
        // dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
        //
        // piano_view_ = new PianoView(this);
        // dock->setAllowedAreas(Qt::BottomDockWidgetArea);
        //
        // resource_view_ = new ResourceView(this);
        // dock->setAllowedAreas(Qt::LeftDockWidgetArea);
        //
        // addDockWidget(Qt::RightDockWidgetArea, dock);
        // addDockWidget(Qt::BottomDockWidgetArea, piano_view_);
        // addDockWidget(Qt::LeftDockWidgetArea, resource_view_);
    }
}
