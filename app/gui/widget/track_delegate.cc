//
// Created by wangrl2016 on 2023/6/27.
//

#include <QPainter>
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
            const QVariant value = index.data(Qt::DisplayRole);
            QString text;
            switch (index.column()) {
                case 0:
                    text =  value.toBool() ? "True" : "False";
            }

            QRect rect = option.rect;
            painter->drawText(rect.x(), rect.y(), text);
        }
    }

    QSize TrackDelegate::sizeHint(const QStyleOptionViewItem& option,
                                  const QModelIndex& index) const {

    }
}
