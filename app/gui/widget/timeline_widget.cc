//
// Created by wangrl2016 on 2023/6/22.
//

#include <glog/logging.h>
#include <QPainter>
#include "app/gui/widget/timeline_widget.h"
#include "app/gui/main_window.h"

namespace app {
    constexpr int kTimelineFixedHeight = 24;
    constexpr int kLongScaleHeight = 12;
    constexpr int kMinPixelPerSecond = 12;
    constexpr int kDefaultPixelPerSecond = 48;
    constexpr int kMaxPixelPerSecond = 512;
    constexpr int kTextPadding = 2;

    TimelineWidget::TimelineWidget(QWidget* parent) :
            QWidget(parent),
            current_interval_(kDefaultPixelPerSecond),
            benchmark_(0.0, 0) {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        setFixedHeight(kTimelineFixedHeight);
        // setAutoFillBackground(true);
    }

    void TimelineWidget::paintEvent(QPaintEvent* event) {
        QPainter painter(this);
        int width = rect().width();
        int count = benchmark_.first;
        for (int i = benchmark_.second; i < width; i += current_interval_) {
            painter.drawLine(i, kTimelineFixedHeight,
                             i, kTimelineFixedHeight - kLongScaleHeight);
            if (current_interval_ < kDefaultPixelPerSecond) {
                // If the scale is too small, it will be drawn at intervals.
                int multiple = kDefaultPixelPerSecond / current_interval_;
                if (count % multiple == 0) {
                    painter.drawText(i + kTextPadding,
                                     kTimelineFixedHeight - kTextPadding,
                                     QString::number(count));
                }
            } else {
                painter.drawText(i + kTextPadding,
                                 kTimelineFixedHeight - kTextPadding,
                                 QString::number(count));
            }
            count++;
        }

        count = benchmark_.first;
        for (int i = benchmark_.second; i > 0; i -= current_interval_) {
            painter.drawLine(i, kTimelineFixedHeight,
                             i, kTimelineFixedHeight - kLongScaleHeight);
            if (current_interval_ < kDefaultPixelPerSecond) {
                // If the scale is too small, it will be drawn at intervals.
                int multiple = kDefaultPixelPerSecond / current_interval_;
                if (count % multiple == 0) {
                    painter.drawText(i + kTextPadding,
                                     kTimelineFixedHeight - kTextPadding,
                                     QString::number(count));
                }
            } else {
                painter.drawText(i + kTextPadding,
                                 kTimelineFixedHeight - kTextPadding,
                                 QString::number(count));
            }
            count--;
        }

        double distance = play_progress_presenter_->PlayProgress() - benchmark_.first;
        int play_progress_index = int(std::round(benchmark_.second + distance * current_interval_));
        painter.drawLine(play_progress_index,
                         rect().y(), play_progress_index, rect().y() + rect().height());
    }

    void TimelineWidget::mousePressEvent(QMouseEvent* event) {
        double distance = event->pos().x() - benchmark_.second;
        double sec = benchmark_.first + distance / current_interval_;
        play_progress_presenter_->NotifyPlayProgress(sec);
    }

    void TimelineWidget::wheelEvent(QWheelEvent* event) {
        int current_pos = int(event->position().x());
        int distance = current_pos - benchmark_.second;
        while (distance < 0) {
            distance += current_interval_;
            benchmark_.first++;
            benchmark_.second -= current_interval_;
        }
        while (distance > current_interval_) {
            distance -= current_interval_;
            benchmark_.first++;
            benchmark_.second += current_interval_;
        }

        current_interval_ -= event->pixelDelta().y();

        if (current_interval_ < kMinPixelPerSecond)
            current_interval_ = kMinPixelPerSecond;
        if (current_interval_ > kMaxPixelPerSecond)
            current_interval_ = kMaxPixelPerSecond;

        update();
    }

    void TimelineWidget::PlayProgressUpdate() {
        update();
    }

    void TimelineWidget::ResetBenchmark() {
        benchmark_ = {0, 0};
    }
}
