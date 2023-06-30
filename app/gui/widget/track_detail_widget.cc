//
// Created by wr on 2023/6/29.
//

#include <QVBoxLayout>
#include "app/gui/widget/track_detail_widget.h"

namespace app {
    TrackDetailWidget::TrackDetailWidget(QWidget* parent) :
            QWidget(parent) {
        // In addition, Windows are always filled with QPalette::Window,
        // unless the WA_OpaquePaintEvent or WA_NoSystemBackground attributes are set.
        setAttribute(Qt::WA_OpaquePaintEvent, true);
    }
}
