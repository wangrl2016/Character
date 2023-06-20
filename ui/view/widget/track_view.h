//
// Created by wr on 2023/6/12.
//

#ifndef CHARACTER_TRACK_VIEW_H
#define CHARACTER_TRACK_VIEW_H

#include <QWidget>
#include "ui/view/widget/model_view.h"

namespace ui {
    class TrackView : public QWidget, public ModelView {
    Q_OBJECT
    public:

    private:
        enum Action {
        kNoAction,
        kMoveTrack,
        kResizeTrack,
    };

    Track* track;

    TrackContainerView * track_container_view;
    };
}

#endif //CHARACTER_TRACK_VIEW_H
