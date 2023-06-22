//
// Created by wangrl2016 on 2023/6/22.
//

#include <QPainter>
#include "app/gui/widget/track_content_widget.h"

namespace app {
    constexpr int kMinTrackHeight = 12;
    constexpr int kDefaultTrackHeight = 48;
    constexpr int kMaxTrackHeight = 96;
    constexpr int kContentPadding = 2;
    TrackContentWidget::TrackContentWidget(QWidget* parent) :
            QWidget(parent),
            track_height_(kDefaultTrackHeight) {
        setAutoFillBackground(true);
    }

    void TrackContentWidget::paintEvent(QPaintEvent* event) {
        QPainter painter(this);
        int height = rect().height();
        for (int i = rect().y() + 2; i < height; i += track_height_) {
            painter.drawLine(rect().x(), i, rect().x() + rect().width(), i);
        }
    }
}
