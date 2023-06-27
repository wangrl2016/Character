//
// Created by wangrl2016 on 2023/6/27.
//

#include "app/gui/widget/track_delegate.h"

namespace app {
    TrackDelegate::TrackDelegate(QObject* parent) :
            QStyledItemDelegate(parent) {

    }

    TrackDelegate::~TrackDelegate() = default;

    void TrackDelegate::paint(QPainter* painter,
                              const QStyleOptionViewItem& option,
                              const QModelIndex& index) const {
        if (index.isValid()) {

        }
    }

    QSize TrackDelegate::sizeHint(const QStyleOptionViewItem& option,
                                  const QModelIndex& index) const {

    }
}
