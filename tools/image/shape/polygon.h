//
// Created by wangrl2016 on 2023/8/31.
//

#ifndef CHARACTER_POLYGON_H
#define CHARACTER_POLYGON_H

#include <QGraphicsPolygonItem>

namespace app {


    class Polygon : public QGraphicsPolygonItem {
    public:
        explicit Polygon(QGraphicsItem* parent = nullptr);

        explicit Polygon(const QPolygonF& polygon,
                         QGraphicsItem* parent = nullptr);

        static Polygon* CreateDefaultPolygon(QGraphicsItem* parent = nullptr);
    };
}


#endif //CHARACTER_POLYGON_H
