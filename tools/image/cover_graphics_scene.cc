//
// Created by wangrl2016 on 2023/8/30.
//

#include <glog/logging.h>
#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>
#include "tools/image/shape/polygon.h"
#include "tools/image/cover_graphics_scene.h"

namespace app {
    CoverGraphicsScene::CoverGraphicsScene(QObject* parent) :
            QGraphicsScene(parent) {
        auto* item = Polygon::CreateDefaultPolygon();
        item->setFlags(Polygon::GraphicsItemFlag::ItemIsSelectable |
                Polygon::GraphicsItemFlag::ItemIsMovable);
        addItem(item);
    }

    void CoverGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
        LOG(INFO) << __FUNCTION__;

        QGraphicsScene::mousePressEvent(event);
    }

    void CoverGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
        QGraphicsScene::mouseMoveEvent(event);
    }

    void CoverGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {

        QGraphicsScene::mouseReleaseEvent(event);
    }
}
