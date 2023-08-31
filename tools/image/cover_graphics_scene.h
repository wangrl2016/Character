//
// Created by wangrl2016 on 2023/8/30.
//

#ifndef CHARACTER_COVER_GRAPHICS_SCENE_H
#define CHARACTER_COVER_GRAPHICS_SCENE_H

#include <QGraphicsScene>
#include <QMouseEvent>

namespace app {
    class CoverGraphicsScene : public QGraphicsScene {
    Q_OBJECT
    public:
        explicit CoverGraphicsScene(QObject* parent = nullptr);

        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

        void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    };
}

#endif //CHARACTER_COVER_GRAPHICS_SCENE_H
