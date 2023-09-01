//
// Created by wangrl2016 on 2023/9/1.
//

#include <QGraphicsItem>
#include "tools/image/item/text.h"

namespace app {
    Text::Text(QGraphicsItem* parent) :
            QGraphicsTextItem(parent) {

    }

    Text::Text(const QString& text, QGraphicsItem* parent) :
            QGraphicsTextItem(text, parent) {
        setFlags(Text::GraphicsItemFlag::ItemIsSelectable |
                 Text::GraphicsItemFlag::ItemIsMovable);
    }
}
