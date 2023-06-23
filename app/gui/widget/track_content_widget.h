//
// Created by wr on 2023/6/22.
//

#ifndef CHARACTER_TRACK_CONTENT_WIDGET_H
#define CHARACTER_TRACK_CONTENT_WIDGET_H

#include <QWidget>
#include "app/presenter/play_progress_view.h"
#include "app/presenter/play_progress_presenter.h"

namespace app {
    class TrackContentWidget : public QWidget,
            public PlayProgressView {
    Q_OBJECT
    public:
        explicit TrackContentWidget(QWidget* parent = nullptr);

        void paintEvent(QPaintEvent* event) override;

        void PlayProgressUpdate() override;

    private:
        int track_height_;
    };
}


#endif //CHARACTER_TRACK_CONTENT_WIDGET_H
