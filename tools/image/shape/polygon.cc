//
// Created by wangrl2016 on 2023/8/31.
//

#include "tools/image/shape/polygon.h"

namespace app {
    constexpr int kDefaultWidth = 80;
    constexpr int kDefaultHeight = 60;
    constexpr int kDefaultMargin = 10;

    Polygon::Polygon(QGraphicsItem* parent) :
            QGraphicsPolygonItem(parent) {
        QPen pen;
        pen.setWidth(2);
        setPen(pen);
    }

    Polygon::Polygon(const QPolygonF& polygon, QGraphicsItem* parent) :
            QGraphicsPolygonItem(polygon, parent) {
        QPen pen;
        pen.setWidth(2);
        setPen(pen);
        setFlags(Polygon::GraphicsItemFlag::ItemIsSelectable |
                 Polygon::GraphicsItemFlag::ItemIsMovable);
    }

    Polygon* Polygon::CreateDefaultPolygon(QGraphicsItem* parent) {
        QPolygonF polygon({QPointF(kDefaultMargin, kDefaultMargin),
                           QPointF(kDefaultWidth, kDefaultMargin),
                           QPointF(kDefaultWidth, kDefaultHeight),
                           QPointF(kDefaultMargin, kDefaultHeight)});
        return new Polygon(polygon, parent);
    }

    void Polygon::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
        QGraphicsPolygonItem::paint(painter, option, widget);
    }
}
