//
// Created by wangrl2016 on 2023/6/21.
//

#ifndef CHARACTER_MAIN_WINDOW_H
#define CHARACTER_MAIN_WINDOW_H

#include <QMainWindow>
#include "app/gui/tab/bottom_tab_widget.h"
#include "app/gui/tab/left_tab_widget.h"
#include "app/gui/toolbar/top_tool_bar.h"
#include "app/gui/widget/timeline_widget.h"
#include "app/gui/widget/track_content_widget.h"
#include "app/gui/widget/track_setting_widget.h"
#include "app/presenter/play_progress_subscriber.h"
#include "app/presenter/play_progress_presenter.h"
#include "app/gui/tab/right_tab_widget.h"
#include "app/gui/toolbar/status_bar.h"

namespace app {
    class MainWindow : public QMainWindow,
            public PlayProgressView {
    Q_OBJECT
    public:
        explicit MainWindow(QWidget* parent = nullptr);

        ~MainWindow() override;

        void Subscribe(PlayProgressPresenter* presenter) override;

        void PlayOrPause();

    private:
        void SetupMenuBar();

        void SetupToolBar();

        void SetupStatusBar();

        bool SetupAudioGraph();

        static void DestroyAudioGraph();

    private:
        TopToolBar* top_tool_bar_;
        StatusBar* status_bar_;

        TimelineWidget* timeline_widget_;
        TrackContentWidget* track_content_widget_;
        TrackSettingWidget* track_setting_widget_;

        LeftTabWidget* left_tab_widget_;
        BottomTabWidget* bottom_tab_widget_;
        RightTabWidget* right_tab_widget_;

        bool is_playing_;
    };
}


#endif //CHARACTER_MAIN_WINDOW_H
