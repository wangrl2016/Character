//
// Created by wangrl2016 on 2023/6/21.
//

#include <glog/logging.h>
#include <QMenu>
#include <QMenuBar>
#include <QShortcut>
#include <QVBoxLayout>
#include "app/gui/dialog/about_dialog.h"
#include "app/gui/toolbar/top_tool_bar.h"
#include "module/audio_graph/audio_bridge.h"
#include "app/gui/main_window.h"

namespace app {
    MainWindow::MainWindow(QWidget* parent) :
            QMainWindow(parent),
            is_playing_(false),
            play_progress_(0) {
        SetupMenuBar();
        SetupToolBar();

        auto* central_widget = new QWidget(this);
        auto h_layout = new QHBoxLayout(central_widget);
        h_layout->setContentsMargins(0, 0, 0, 0);
        h_layout->setSpacing(0);

        track_setting_widget_ = new TrackSettingWidget(central_widget);

        auto* right_widget = new QWidget(central_widget);
        auto v_layout = new QVBoxLayout(right_widget);
        v_layout->setContentsMargins(0, 0, 0, 0);
        v_layout->setSpacing(0);

        timeline_widget_ = new TimelineWidget(right_widget);
        v_layout->addWidget(timeline_widget_);

        track_content_widget_ = new TrackContentWidget(right_widget);
        v_layout->addWidget(track_content_widget_);

        h_layout->addWidget(track_setting_widget_);
        h_layout->addWidget(right_widget);

        setCentralWidget(central_widget);

        SetupAudioGraph();

        connect(this, &MainWindow::PlayProgressUpdate,
                timeline_widget_, &TimelineWidget::PlayProgressReceive);
    }

    MainWindow::~MainWindow() {
        DestroyAudioGraph();
    }

    void MainWindow::PlayOrPause() {
        is_playing_ = !is_playing_;
        if (is_playing_) {
            audio_graph::AudioBridge::Seek(play_progress_);
            audio_graph::AudioBridge::StartBeat();
        } else {
            audio_graph::AudioBridge::StopBeat();
        }
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

    bool MainWindow::SetupAudioGraph() {
        if (!audio_graph::AudioBridge::Create()) {
            return false;
        }
        if (!audio_graph::AudioBridge::Start()) {
            return false;
        }
        audio_graph::AudioBridge::RegisterPlayProgressHandler([this](double sec) {
            play_progress_ = sec;
            emit PlayProgressUpdate(sec);
        });
        return true;
    }

    void MainWindow::DestroyAudioGraph() {
        audio_graph::AudioBridge::RegisterPlayProgressHandler(nullptr);
        audio_graph::AudioBridge::Stop();
        audio_graph::AudioBridge::Destroy();
    }
}
