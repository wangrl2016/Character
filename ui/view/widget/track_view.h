//
// Created by wr on 2023/6/12.
//

#ifndef CHARACTER_TRACK_VIEW_H
#define CHARACTER_TRACK_VIEW_H

#include <QWidget>
#include "ui/view/widget/model_view.h"
#include "track_content_widget.h"
#include "track_setting_widget.h"

namespace ui {
    class Clip;
    class Track;
    class TrackContainerView;

    class TrackView : public QWidget, public ModelView {
    Q_OBJECT
    public:
        TrackView(Track* track, TrackContainerView* tcv);

        ~TrackView() override = default;

        inline Track* track() const { return track_; }

    private:
        enum Action {
            kNoAction,
            kMoveTrack,
            kResizeTrack,
        };

        Track* track_;

        TrackContainerView * track_container_view_;

        TrackContentWidget* track_content_widget_;
        TrackSettingWidget* track_setting_widget_;
    };
}

#endif //CHARACTER_TRACK_VIEW_H
