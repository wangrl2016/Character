//
// Created by wangrl2016 on 2023/8/30.
//

#ifndef CHARACTER_COVER_GRAPHICS_VIEW_H
#define CHARACTER_COVER_GRAPHICS_VIEW_H

#include <QGraphicsView>

namespace app {
    class CoverGraphicsView : public QGraphicsView {
    Q_OBJECT
    public:
        explicit CoverGraphicsView(QWidget* parent = nullptr);

        explicit CoverGraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr);

        void mousePressEvent(QMouseEvent* event) override;

        void mouseMoveEvent(QMouseEvent* event) override;

        void mouseReleaseEvent(QMouseEvent* event) override;

        void dragEnterEvent(QDragEnterEvent* event) override;

    private:
        QGraphicsPixmapItem* item_;
    };
}

#endif //CHARACTER_COVER_GRAPHICS_VIEW_H
