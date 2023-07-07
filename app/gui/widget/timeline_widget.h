//
// Created by wangrl2016 on 2023/6/22.
//

#ifndef CHARACTER_TIMELINE_WIDGET_H
#define CHARACTER_TIMELINE_WIDGET_H

#include <QWheelEvent>
#include <QWidget>
#include "app/presenter/play_progress_view.h"
#include "app/presenter/play_progress_presenter.h"

namespace app {
    class TimelineWidget : public QWidget,
            public PlayProgressView {
    Q_OBJECT
    public:
        explicit TimelineWidget(QWidget* parent = nullptr);

        void paintEvent(QPaintEvent* event) override;

        void mousePressEvent(QMouseEvent* event) override;

        void mouseMoveEvent(QMouseEvent* event) override;

        void mouseReleaseEvent(QMouseEvent* event) override;

        void wheelEvent(QWheelEvent* event) override;

        void PlayProgressUpdate() override;

        void ResetBenchmark();
    private:
        int current_interval_;
        // The pixel value corresponding to the current time.
        std::pair<int, int> benchmark_;

        // Record the state of the mouse at the previous moment.
        QPoint temp_prev_pos_;
        bool adjust_loop_;
    };
}

#endif //CHARACTER_TIMELINE_WIDGET_H
