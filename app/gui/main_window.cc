//
// Created by wangrl2016 on 2023/6/21.
//

#include <glog/logging.h>
#include <QMenu>
#include <QMenuBar>
#include <QShortcut>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QStandardPaths>
#include "app/gui/dialog/about_dialog.h"
#include "app/gui/toolbar/top_tool_bar.h"
#include "module/audio_graph/audio_bridge.h"
#include "app/gui/main_window.h"
#include "app/presenter/play_progress_presenter.h"

namespace app {
    MainWindow::MainWindow(QWidget* parent) :
            QMainWindow(parent),
            is_playing_(false) {
        setStyleSheet(/* "QWidget {"
                      "    background-color: #FFFBFE;"
                      "}" */
                      "QMainWindow QToolBar {"
                      "    spacing: 0px;"
                      "}"
                      "QMainWindow QToolBar QToolButton:hover {"
                      "    background-color: rgba(255, 00, 255, 0.1);"
                      "}");

        SetupMenuBar();
        SetupToolBar();
        SetupStatusBar();

        auto* widget = new QWidget(this);
        auto layout = new QVBoxLayout(widget);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);

        auto* central_widget = new QWidget(widget);
        auto h_layout = new QHBoxLayout(central_widget);
        h_layout->setContentsMargins(0, 0, 0, 0);
        h_layout->setSpacing(0);

        // track_setting_widget_ = new TrackSettingWidget(central_widget);
        left_tab_widget_ = new LeftTabWidget(central_widget);
        right_tab_widget_ = new RightTabWidget(central_widget);

        auto* right_widget = new QWidget(central_widget);
        auto v_layout = new QVBoxLayout(right_widget);
        v_layout->setContentsMargins(0, 0, 0, 0);
        v_layout->setSpacing(0);

        timeline_widget_ = new TimelineWidget(right_widget);
        v_layout->addWidget(timeline_widget_);

        track_content_widget_ = new TrackContentWidget(right_widget);
        v_layout->addWidget(track_content_widget_);

        // h_layout->addWidget(track_setting_widget_);
        h_layout->addWidget(left_tab_widget_);
        h_layout->addWidget(right_widget);
        h_layout->addWidget(right_tab_widget_);

        bottom_tab_widget_ = new BottomTabWidget(widget);
        layout->addWidget(central_widget);
        layout->addWidget(bottom_tab_widget_);

        setCentralWidget(widget);

        SetupAudioGraph();
    }

    MainWindow::~MainWindow() {
        DestroyAudioGraph();
    }

    void MainWindow::Subscribe(PlayProgressPresenter* presenter) {
        PlayProgressView::Subscribe(presenter);

        timeline_widget_->Subscribe(presenter);
        track_content_widget_->Subscribe(presenter);
    }

    void MainWindow::PlayOrPause() {
        is_playing_ = !is_playing_;
        if (is_playing_) {
            audio_graph::AudioBridge::Seek(play_progress_presenter_->PlayProgress());
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

        // open
        auto* open_action = new QAction(QIcon(), tr("Open"), file_menu);
        open_action->setShortcut(QKeySequence::Open);
        connect(open_action, &QAction::triggered, this, [&]() {
            auto target_path = QFileDialog::getOpenFileName(
                    this,
                    QStringLiteral("Open"),
                    QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));

            LOG(INFO) << "Open file path: " << target_path.toStdString();
        });
        file_menu->addAction(open_action);

        // open recent
        auto* open_recent_action = new QAction(QIcon(), tr("Open Recent"), file_menu);
        file_menu->addAction(open_recent_action);
    }

    void MainWindow::SetupToolBar() {
#ifdef Q_OS_MACOS
        setUnifiedTitleAndToolBarOnMac(true);
#endif
        top_tool_bar_ = new TopToolBar(this);
        addToolBar(top_tool_bar_);
    }

    void MainWindow::SetupStatusBar() {
        status_bar_ = new StatusBar(this);
        setStatusBar(status_bar_);
    }

    bool MainWindow::SetupAudioGraph() {
        if (!audio_graph::AudioBridge::Create()) {
            return false;
        }
        if (!audio_graph::AudioBridge::Start()) {
            return false;
        }
        audio_graph::AudioBridge::RegisterPlayProgressHandler([this](double sec) {
            play_progress_presenter_->NotifyPlayProgress(sec);
        });
        return true;
    }

    void MainWindow::DestroyAudioGraph() {
        audio_graph::AudioBridge::RegisterPlayProgressHandler(nullptr);
        audio_graph::AudioBridge::Stop();
        audio_graph::AudioBridge::Destroy();
    }
}
