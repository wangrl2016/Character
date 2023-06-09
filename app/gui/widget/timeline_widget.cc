//
// Created by wangrl2016 on 2023/6/22.
//

#include <glog/logging.h>
#include <QPainter>
#include "app/gui/widget/timeline_widget.h"
#include "app/gui/main_window.h"
#include "app/gui/style/color_constant.h"

namespace app {
    constexpr int kTimelineFixedHeight = 24;
    constexpr int kLongScaleHeight = 12;
    constexpr int kMinPixelPerSecond = 24;
    constexpr int kDefaultPixelPerSecond = 48;
    constexpr int kMaxPixelPerSecond = 512;
    constexpr int kTextPadding = 2;
    constexpr int kLoopPadding = 10;

    TimelineWidget::TimelineWidget(QWidget* parent) :
            QWidget(parent),
            current_interval_(kDefaultPixelPerSecond),
            benchmark_(0.0, 0) {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        setFixedHeight(kTimelineFixedHeight);
        setMouseTracking(true);
        // setAutoFillBackground(true);
    }

    void TimelineWidget::paintEvent(QPaintEvent* event) {
        QWidget::paintEvent(event);

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

        double loop_start = play_progress_presenter_->LoopStart() - benchmark_.first;
        int start_index = int(std::round(benchmark_.second + loop_start * current_interval_));
        double loop_end = play_progress_presenter_->LoopEnd() - benchmark_.first;
        int end_index = int(std::round(benchmark_.second + loop_end * current_interval_));
        painter.setBrush(QBrush(QColor(kColorPrimary70)));
        painter.setPen(Qt::NoPen);
        painter.drawRect(start_index,
                         rect().y(),
                         end_index,
                         rect().y() + kTimelineFixedHeight - kLongScaleHeight);
    }

    void TimelineWidget::mousePressEvent(QMouseEvent* event) {
        if (adjust_loop_) {
            temp_prev_pos_ = event->pos();
        } else {
            double distance = event->pos().x() - benchmark_.second;
            double sec = benchmark_.first + distance / current_interval_;
            play_progress_presenter_->NotifyPlayProgress(sec);
        }
    }

    void TimelineWidget::mouseMoveEvent(QMouseEvent* event) {
        int x = event->pos().x();

        if (adjust_loop_) {

        }

        double loop_start = play_progress_presenter_->LoopStart();
        int start_index = int(std::round(benchmark_.second + loop_start * current_interval_));
        double loop_end = play_progress_presenter_->LoopEnd();
        int end_index = int(std::round(benchmark_.second + loop_end * current_interval_));

        if ((start_index - kLoopPadding < x && x < start_index + kLoopPadding) ||
                (end_index - kLoopPadding < x && x < end_index + kLoopPadding)) {
            setCursor(Qt::CursorShape::SizeHorCursor);
            adjust_loop_ = true;
        } else {
            adjust_loop_ = false;
            setCursor(Qt::CursorShape::ArrowCursor);
        }
    }

    void TimelineWidget::mouseReleaseEvent(QMouseEvent* event) {
        adjust_loop_ = false;
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
