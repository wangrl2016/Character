//
// Created by wr on 2023/6/22.
//

#ifndef CHARACTER_TRACK_CONTENT_WIDGET_H
#define CHARACTER_TRACK_CONTENT_WIDGET_H

#include <QWidget>

namespace app {
    class TrackContentWidget : public QWidget {
    Q_OBJECT
    public:
        explicit TrackContentWidget(QWidget* parent = nullptr);

        void paintEvent(QPaintEvent* event) override;

    public slots:
        void PlayProgressReceive(double sec);
    private:
        int track_height_;
    };
}


#endif //CHARACTER_TRACK_CONTENT_WIDGET_H
