//
// Created by wr on 2023/7/2.
//

#include <Qpainter>
#include "app/gui/widget/instrument/plucked_string.h"

namespace app {
    PluckedString::PluckedString(QWidget* widget) :
            QWidget(widget) {
        // setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    PluckedString::~PluckedString() {

    }

    void PluckedString::paintEvent(QPaintEvent* event) {
        QPainter painter(this);


    }
}
