//
// Created by wangrl2016 on 2023/8/31.
//

#include "tools/image/item/polygon.h"

namespace app {
    constexpr int kDefaultWidth = 80;
    constexpr int kDefaultPenWidth = 2;
    constexpr int kDefaultHeight = 60;
    constexpr int kDefaultMargin = 10;

    Polygon::Polygon(QGraphicsItem* parent) :
            QGraphicsPolygonItem(parent) {
        Initialize();
    }

    Polygon::Polygon(const QPolygonF& polygon, QGraphicsItem* parent) :
            QGraphicsPolygonItem(polygon, parent) {
        Initialize();
    }

    void Polygon::paint(QPainter* painter,
                        const QStyleOptionGraphicsItem* option,
                        QWidget* widget) {
        QGraphicsPolygonItem::paint(painter, option, widget);

        if (isSelected()) {

        }
    }

    void Polygon::Initialize() {
        QPen pen;
        pen.setWidth(kDefaultPenWidth);
        setPen(pen);
        setFlags(Polygon::GraphicsItemFlag::ItemIsSelectable |
                 Polygon::GraphicsItemFlag::ItemIsMovable);
    }
}
