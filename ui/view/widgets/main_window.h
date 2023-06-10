//
// Created by wangrl2016 on 2023/6/2.
//

#ifndef CHARACTER_MAIN_WINDOW_H
#define CHARACTER_MAIN_WINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QPushButton>
#include "ui/view/widgets/waveform_widget.h"
#include "ui/view/widgets/piano_view.h"

namespace ui {
    class MainWindow : public QMainWindow {
    Q_OBJECT
    public:
        MainWindow();

        ~MainWindow() override;

    public slots:
        bool NewFile();

        bool OpenFile();

        void Play();

        void Pause();

        void PlayOrPause();

        void Stop();

    private:
        void CreateActions();

        void CreateMenus();

        void CreateToolBar();

        void CreateDockWindows();

        QAction* file_new_action_;
        QAction* file_open_action_;

        QPushButton* play_or_pause_button_;
        QAction* play_action_;
        QAction* pause_action_;
        QAction* stop_action_;

    private:
        PianoView* piano_view_;

        WaveformWidget* waveform_widget_;
        QToolBar* tool_bar_;

        bool is_playing_ = false;
    };
}


#endif //CHARACTER_MAIN_WINDOW_H
