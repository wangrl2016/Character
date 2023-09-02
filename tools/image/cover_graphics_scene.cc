//
// Created by wangrl2016 on 2023/8/30.
//

#include <glog/logging.h>
#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>
#include <QFileInfo>
#include <QIcon>
#include "tools/image/item/polygon.h"
#include "tools/image/item/text.h"
#include "tools/image/cover_graphics_scene.h"
#include "tools/image/item/pixmap.h"
#include "tools/image/item/color_item.h"
#include "tools/image/item/robot.h"

namespace app {
    CoverGraphicsScene::CoverGraphicsScene(QObject* parent) :
            QGraphicsScene(parent) {
        for (int i = 0; i < 10; i++) {
            auto* item = new ColorItem;
            item->setPos(150 + ::sin((i * 6.28) / 10.0) * 150,
                         150 + ::cos((i * 6.28) / 10.0) * 150);
            addItem(item);
        }

        auto* robot = new Robot;
        robot->setTransform(QTransform::fromScale(1.2, 1.2), true);
        robot->setPos(100, 100);
        addItem(robot);
    }

    void CoverGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
        // LOG(INFO) << __FUNCTION__;

        QGraphicsScene::mousePressEvent(event);
    }

    void CoverGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
        QGraphicsScene::mouseMoveEvent(event);
    }

    void CoverGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {

        QGraphicsScene::mouseReleaseEvent(event);
    }
}
