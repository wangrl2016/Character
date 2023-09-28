//
// Created by wangrl2016 on 2023/8/30.
//

#include <QDragEnterEvent>
#include <QMimeData>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <glog/logging.h>
#include "tools/image/cover_graphics_view.h"

namespace app {
    CoverGraphicsView::CoverGraphicsView(QWidget* parent) :
            QGraphicsView(parent) {
        setAcceptDrops(true);
    }

    CoverGraphicsView::CoverGraphicsView(QGraphicsScene* scene, QWidget* parent) :
            QGraphicsView(scene, parent) {

    }

    void CoverGraphicsView::mousePressEvent(QMouseEvent* event) {
        qDebug() << event->scenePosition();

        QGraphicsView::mousePressEvent(event);
    }

    void CoverGraphicsView::mouseMoveEvent(QMouseEvent* event) {
        QGraphicsView::mouseMoveEvent(event);
    }

    void CoverGraphicsView::mouseReleaseEvent(QMouseEvent* event) {
        QGraphicsView::mouseReleaseEvent(event);
    }

    void CoverGraphicsView::dragEnterEvent(QDragEnterEvent* event) {
        // Need to parse image format
        event->accept();
        LOG(INFO) << __FUNCTION__;
        QPixmap pixmap(event->mimeData()->urls()[0].toLocalFile());
        LOG(INFO) << "Pixmap size " << pixmap.size().width() << " x " << pixmap.size().height();

        scene()->setSceneRect(pixmap.rect());

        item_ = new QGraphicsPixmapItem(pixmap);

        scene()->addItem(item_);

        // scene()->addPixmap(pixmap);

        update();
    }
}
