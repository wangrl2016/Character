//
// Created by wangrl2016 on 2023/9/1.
//

#ifndef CHARACTER_TEXT_H
#define CHARACTER_TEXT_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QString>

namespace app {
    class Text : public QGraphicsTextItem {
    public:
        explicit Text(QGraphicsItem* parent = nullptr);

        explicit Text(const QString& text, QGraphicsItem* parent = nullptr);
    };
}

#endif //CHARACTER_TEXT_H
