//
// Created by wangrl2016 on 2023/8/31.
//

#include "tools/image/shape/polygon.h"

namespace app {
    constexpr int kDefaultWidth = 40;
    constexpr int kDefaultHeight = 30;

    Polygon::Polygon(QGraphicsItem* parent) :
            QGraphicsPolygonItem(parent) {

    }

    Polygon::Polygon(const QPolygonF& polygon, QGraphicsItem* parent) :
            QGraphicsPolygonItem(polygon, parent) {

    }

    Polygon* Polygon::CreateDefaultPolygon(QGraphicsItem* parent) {
        QPolygonF polygon({QPointF(0, 0),
                           QPointF(kDefaultWidth, 0),
                           QPointF(kDefaultWidth, kDefaultHeight),
                           QPointF(0, kDefaultHeight)});
        return new Polygon(polygon, parent);
    }
}
