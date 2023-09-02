//
// Created by wangrl2016 on 2023/9/2.
//

#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include "tools/image/item/robot.h"

namespace app {
    RobotPart::RobotPart(QGraphicsItem* parent)
            : QGraphicsObject(parent), color_(Qt::lightGray) {
        setAcceptDrops(true);
    }

    void RobotPart::dragEnterEvent(QGraphicsSceneDragDropEvent* event) {
        if (event->mimeData()->hasColor()) {
            event->setAccepted(true);
            drag_over_ = true;
            update();
        } else {
            event->setAccepted(false);
        }
    }

    void RobotPart::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {
        Q_UNUSED(event);
        drag_over_ = false;
        update();
    }

    void RobotPart::dropEvent(QGraphicsSceneDragDropEvent *event) {
        drag_over_ = false;
        if (event->mimeData()->hasColor())
            color_ = qvariant_cast<QColor>(event->mimeData()->colorData());
        update();
    }

    RobotHead::RobotHead(QGraphicsItem* parent) :
            RobotPart(parent) {
    }

    QRectF RobotHead::boundingRect() const {
        return { 50, 50, 30,  50};
    }

    void RobotHead::paint(QPainter* painter,
                          const QStyleOptionGraphicsItem* option,
                          QWidget* widget) {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        if (pixmap_.isNull()) {
            painter->setBrush(drag_over_ ? color_.lighter(130) : color_);
            painter->drawRoundedRect(90, 70, 120, 150, 25, 25, Qt::RelativeSize);
            painter->setBrush(Qt::white);
            painter->drawEllipse(93, 77, 7, 7);
        } else {
            painter->drawPixmap(QPointF(60, 100), pixmap_);
        }
    }

    void RobotHead::dragEnterEvent(QGraphicsSceneDragDropEvent* event) {

    }

    void RobotHead::dropEvent(QGraphicsSceneDragDropEvent* event) {

    }

    QRectF RobotTorso::boundingRect() const {
        return {50, 50, 60, 60};
    }

    void RobotTorso::paint(QPainter* painter,
                           const QStyleOptionGraphicsItem* option,
                           QWidget* widget) {

    }

    RobotLimb::RobotLimb(QGraphicsItem* parent) :
            RobotPart(parent) {

    }

    QRectF RobotLimb::boundingRect() const {
        return {50, 50, 40, 10};
    }

    void RobotLimb::paint(QPainter* painter,
                          const QStyleOptionGraphicsItem* option,
                          QWidget* widget) {

    }

    Robot::Robot(QGraphicsItem* parent) :
            RobotPart(parent) {
        setFlag(ItemHasNoContents);

        QGraphicsObject* torso_item = new RobotTorso(this);
        QGraphicsObject* head_item = new RobotHead(torso_item);

        head_item->setPos(100, 100);

        auto* animation = new QParallelAnimationGroup(this);

        auto* head_animation = new QPropertyAnimation(head_item, "rotation");
        head_animation->setStartValue(50);
        head_animation->setEndValue(80);

        animation->setLoopCount(-1);
        animation->start();
    }

    QRectF Robot::boundingRect() const {
        return {};
    }

    void Robot::paint(QPainter* painter,
                      const QStyleOptionGraphicsItem* option,
                      QWidget* widget) {
        Q_UNUSED(painter);
        Q_UNUSED(option);
        Q_UNUSED(widget);
    }
}
