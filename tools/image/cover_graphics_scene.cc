//
// Created by wangrl2016 on 2023/8/30.
//

#include <glog/logging.h>
#include <QGraphicsPolygonItem>
#include "tools/image/cover_graphics_scene.h"

namespace app {
    CoverGraphicsScene::CoverGraphicsScene(QObject* parent) :
            QGraphicsScene(parent) {

    }

    void CoverGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
        LOG(INFO) << __FUNCTION__;


        auto* item = new QGraphicsPolygonItem(QPolygonF({QPointF(0, 0), QPointF(10, 10), QPointF(0, 10)}));

        addItem(item);


        QGraphicsScene::mousePressEvent(event);
    }

    void CoverGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
        QGraphicsScene::mouseMoveEvent(event);
    }

    void CoverGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
        QGraphicsScene::mouseReleaseEvent(event);
    }
}
