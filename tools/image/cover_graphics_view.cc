//
// Created by wangrl2016 on 2023/8/30.
//

#include <glog/logging.h>
#include "tools/image/cover_graphics_view.h"

namespace app {
    CoverGraphicsView::CoverGraphicsView(QWidget* parent) :
            QGraphicsView(parent) {

    }

    CoverGraphicsView::CoverGraphicsView(QGraphicsScene* scene, QWidget* parent) :
            QGraphicsView(scene, parent) {

    }

    void CoverGraphicsView::mousePressEvent(QMouseEvent* event) {
        LOG(INFO) << __FUNCTION__;
        QGraphicsView::mousePressEvent(event);
    }

    void CoverGraphicsView::mouseMoveEvent(QMouseEvent* event) {
        QGraphicsView::mouseMoveEvent(event);
    }

    void CoverGraphicsView::mouseReleaseEvent(QMouseEvent* event) {
        QGraphicsView::mouseReleaseEvent(event);
    }
}
