//
// Created by wangrl2016 on 2023/6/13.
//

#include <utility>
#include <QVBoxLayout>
#include "ui/view/widget/track_container_view.h"

namespace ui {
    TrackContainerView::TrackContainerView(std::shared_ptr<TrackContainer> track_container)
            : ModelView(nullptr, std::make_shared<QWidget>(this)),
              track_container_(std::move(track_container)) {
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
