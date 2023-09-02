//
// Created by wangrl2016 on 2023/9/2.
//

#include "tools/image/item/robot.h"

namespace app {
    RobotPart::RobotPart(QGraphicsItem* parent)
            : QGraphicsObject(parent), color_(Qt::lightGray) {
        setAcceptDrops(true);
    }

    void RobotPart::dragEnterEvent(QGraphicsSceneDragDropEvent* event) {
        if (event->mimeData()->hasColor()) {
            event->setAccepted(true);
            drag_over_ = true;
            update();
        } else {
            event->setAccepted(false);
        }
    }

    void RobotPart::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {
        Q_UNUSED(event);
        drag_over_ = false;
        update();
    }

    void RobotPart::dropEvent(QGraphicsSceneDragDropEvent *event) {
        drag_over_ = false;
        if (event->mimeData()->hasColor())
            color_ = qvariant_cast<QColor>(event->mimeData()->colorData());
        update();
    }
}
