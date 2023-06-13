//
// Created by wangrl2016 on 2023/6/2.
//

#ifndef CHARACTER_MAIN_WINDOW_H
#define CHARACTER_MAIN_WINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QPushButton>
#include "ui/view/widget/waveform_widget.h"
#include "ui/view/widget/piano_view.h"
#include "ui/view/widget/resource_view.h"

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

        QIcon play_icon_;
        QIcon pause_icon_;

        QTabWidget* left_tab_widget_;
        QTabWidget* right_tab_widget_;
        QTabWidget* down_tab_widget_;

        PianoView* piano_view_;
        ResourceView* resource_view_;

        WaveformWidget* waveform_widget_;
        QWidget* central_widget_;
        QToolBar* tool_bar_;

        bool is_playing_ = false;
    };
}


#endif //CHARACTER_MAIN_WINDOW_H
