//
// Created by wangrl2016 on 2023/9/2.
//

#ifndef CHARACTER_ROBOT_H
#define CHARACTER_ROBOT_H

#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsObject>
#include <QMimeData>

namespace app {
    class RobotPart : public QGraphicsObject {
    public:
        RobotPart(QGraphicsItem* parent = nullptr);

    protected:
        void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;

        void dragLeaveEvent(QGraphicsSceneDragDropEvent* event) override;

        void dropEvent(QGraphicsSceneDragDropEvent* event) override;

        QColor color_ = Qt::lightGray;
        bool drag_over_ = false;
    };

    class RobotHead : public RobotPart {
    public:
        RobotHead(QGraphicsItem* parent = nullptr);

        QRectF boundingRect() const override;

        void paint(QPainter* painter,
                   const QStyleOptionGraphicsItem* option,
                   QWidget* widget = nullptr) override;

    protected:
        void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;

        void dropEvent(QGraphicsSceneDragDropEvent* event) override;

    private:
        QPixmap pixmap_;
    };

    class RobotTorso : public RobotPart {
    public:
        QRectF boundingRect() const override;

        void paint(QPainter* painter,
                   const QStyleOptionGraphicsItem* option,
                   QWidget* widget = nullptr) override;
    };

    class Robot : public RobotPart {
    public:
        Robot(QGraphicsItem* parent = nullptr);

        QRectF boundingRect() const override;

        void paint(QPainter* painter,
                   const QStyleOptionGraphicsItem* option,
                   QWidget* widget = nullptr) override;
    };
}

#endif //CHARACTER_ROBOT_H
