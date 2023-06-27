//
// Created by wangrl2016 on 2023/6/27.
//

#ifndef CHARACTER_TRACK_DELEGATE_H
#define CHARACTER_TRACK_DELEGATE_H

#include <QStyledItemDelegate>

namespace app {
    class TrackDelegate : public QStyledItemDelegate {
    Q_OBJECT
    public:
        explicit TrackDelegate(QObject* parent = nullptr);

        ~TrackDelegate() override;

        void paint(QPainter *painter,
                   const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

        QSize sizeHint(const QStyleOptionViewItem &option,
                       const QModelIndex &index) const override;
    };
}

#endif //CHARACTER_TRACK_DELEGATE_H
