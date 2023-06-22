//
// Created by wangrl2016 on 2023/6/21.
//

#ifndef CHARACTER_MAIN_WINDOW_H
#define CHARACTER_MAIN_WINDOW_H

#include <QMainWindow>
#include "app/gui/widget/timeline_widget.h"
#include "app/gui/widget/track_content_widget.h"
#include "app/gui/widget/track_setting_widget.h"

namespace app {
    class MainWindow : public QMainWindow {
    Q_OBJECT
    public:
        explicit MainWindow(QWidget* parent = nullptr);

        ~MainWindow();

        void PlayOrPause();

        [[nodiscard]] double play_progress() const { return play_progress_; }

    private:
        void SetupMenuBar();

        void SetupToolBar();

        bool SetupAudioGraph();

        static void DestroyAudioGraph();

    signals:
        void PlayProgressUpdate(double sec);

    private:
        TimelineWidget* timeline_widget_;
        TrackContentWidget* track_content_widget_;
        TrackSettingWidget* track_setting_widget_;

        bool is_playing_;
        double play_progress_;
    };
}


#endif //CHARACTER_MAIN_WINDOW_H
