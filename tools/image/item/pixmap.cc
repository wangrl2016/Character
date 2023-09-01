//
// Created by wangrl2016 on 2023/9/1.
//

#include "tools/image/item/pixmap.h"

namespace app {
    Pixmap::Pixmap(QGraphicsItem* parent) :
            QGraphicsPixmapItem(parent) {

    }

    Pixmap::Pixmap(const QPixmap& pixmap, QGraphicsItem* parent) :
            QGraphicsPixmapItem(pixmap, parent) {

    }
}
