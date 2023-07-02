//
// Created by wr on 2023/7/2.
//

#ifndef CHARACTER_PLUCKED_STRING_H
#define CHARACTER_PLUCKED_STRING_H

#include <QWidget>

namespace app {
    class PluckedString : public QWidget {
    Q_OBJECT
    public:
        PluckedString(QWidget* widget);

        ~PluckedString();

        void paintEvent(QPaintEvent *event) override;
    };
}

#endif //CHARACTER_PLUCKED_STRING_H
