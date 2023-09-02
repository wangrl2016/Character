//
// Created by wangrl2016 on 2023/9/1.
//

#ifndef CHARACTER_COLOR_ITEM_H
#define CHARACTER_COLOR_ITEM_H

#include <QGraphicsItem>

namespace app {
    class ColorItem : public QGraphicsItem {
    public:
        ColorItem();

        QRectF boundingRect() const override;

        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

        void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    private:
        QColor color;
    };
}


#endif //CHARACTER_COLOR_ITEM_H
