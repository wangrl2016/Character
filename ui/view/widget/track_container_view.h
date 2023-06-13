//
// Created by wangrl2016 on 2023/6/13.
//

#ifndef CHARACTER_TRACK_CONTAINER_VIEW_H
#define CHARACTER_TRACK_CONTAINER_VIEW_H

#include <QWidget>
#include "ui/model/track_container.h"
#include "ui/view/widget/model_view.h"

namespace ui {
    class TrackContainerView : public QWidget, public ModelView {
    Q_OBJECT
    public:
        TrackContainerView(std::shared_ptr<TrackContainer> track_container);

        ~TrackContainerView() override;

        std::shared_ptr<TrackContainer> Model() {
            return track_container_;
        }

        void ClearAllTracks();

    signals:
        void PositionChanged(int pos);

        void TracksRealigned();

    private:
        std::shared_ptr<TrackContainer> track_container_;
    };
}

#endif //CHARACTER_TRACK_CONTAINER_VIEW_H
