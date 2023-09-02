//
// Created by wangrl2016 on 2023/9/1.
//

#include <QApplication>
#include <QCursor>
#include <QDrag>
#include <QGraphicsSceneMouseEvent>
#include <QMimeData>
#include <QPainter>
#include <QRandomGenerator>
#include <QWidget>
#include "tools/image/item/color_item.h"

namespace app {
    ColorItem::ColorItem() :
        color(QRandomGenerator::global()->bounded(256),
              QRandomGenerator::global()->bounded(256),
              QRandomGenerator::global()->bounded(256)) {
        setToolTip(QString("QColor(%1, %2, %3)\n%4")
                           .arg(color.red()).arg(color.green()).arg(color.blue())
                           .arg("Click and drag this color onto the robot!"));
        setCursor(Qt::OpenHandCursor);
        setAcceptedMouseButtons(Qt::LeftButton);
    }

    QRectF ColorItem::boundingRect() const {
        return {0, 0, 50, 50};
    }

    void ColorItem::paint(QPainter* painter,
                          const QStyleOptionGraphicsItem* option,
                          QWidget* widget) {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::darkGray);
        painter->drawEllipse(5, 5, 45, 45);
        painter->setPen(QPen(Qt::black, 1));
        painter->setBrush(QBrush(color));
        painter->drawEllipse(10, 10, 40, 40);
    }

    void ColorItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
        setCursor(Qt::ClosedHandCursor);
    }

    void ColorItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
        if (QLineF(event->screenPos(), event->buttonDownScenePos(Qt::LeftButton)).length()
                < QApplication::startDragDistance()) {
            return;
        }

        auto* drag = new QDrag(event->widget());
        auto* mime = new QMimeData;
        drag->setMimeData(mime);

        mime->setColorData(color);

        mime->setText(QString("#%1%2%3")
                              .arg(color.red(), 2, 16, QLatin1Char('0'))
                              .arg(color.green(), 2, 16, QLatin1Char('0'))
                              .arg(color.blue(), 2, 16, QLatin1Char('0')));

        QPixmap pixmap(100, 100);
        pixmap.fill(Qt::white);

        QPainter painter(&pixmap);
        painter.translate(5, 5);
        painter.setRenderHint(QPainter::Antialiasing);
        paint(&painter, nullptr, nullptr);
        painter.end();

        pixmap.setMask(pixmap.createHeuristicMask());

        drag->setPixmap(pixmap);
        drag->setHotSpot(QPoint(15, 20));

        drag->exec();
        setCursor(Qt::OpenHandCursor);
    }

    void ColorItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
        setCursor(Qt::OpenHandCursor);
    }
}
