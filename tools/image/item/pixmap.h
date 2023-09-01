//
// Created by wangrl2016 on 2023/9/1.
//

#ifndef CHARACTER_PIXMAP_H
#define CHARACTER_PIXMAP_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

namespace app {
    class Pixmap : public QGraphicsPixmapItem {
    public:
        explicit Pixmap(QGraphicsItem* parent = nullptr);

        explicit Pixmap(const QPixmap& pixmap, QGraphicsItem* parent = nullptr);
    };
}

#endif //CHARACTER_PIXMAP_H
