//
// Created by wangrl2016 on 2023/6/22.
//

#ifndef CHARACTER_TIMELINE_WIDGET_H
#define CHARACTER_TIMELINE_WIDGET_H

#include <QWheelEvent>
#include <QWidget>

namespace app {
    class TimelineWidget : public QWidget {
    Q_OBJECT
    public:
        explicit TimelineWidget(QWidget* parent = nullptr);

        void paintEvent(QPaintEvent* event) override;

        void wheelEvent(QWheelEvent* event) override;

    private:
        int current_interval_;
        // The pixel value corresponding to the current time.
        std::pair<int, int> benchmark_;

    };
}

#endif //CHARACTER_TIMELINE_WIDGET_H
