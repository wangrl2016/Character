//
// Created by wangrl2016 on 2023/6/13.
//

#include <utility>
#include <QVBoxLayout>
#include "ui/view/widget/track_container_view.h"

namespace ui {
    TrackContainerView::TrackContainerView(TrackContainer* track_container)
            : ModelView(nullptr, this),
              track_container_(track_container) {
        // keeps the direction of the widget
        setLayoutDirection(Qt::LeftToRight);

        auto layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);


    }

    TrackContainerView::~TrackContainerView() {

    }

    void TrackContainerView::ClearAllTracks() {

    }


}
