//
// Created by wr on 2023/7/2.
//

#ifndef CHARACTER_PLUCKED_STRING_H
#define CHARACTER_PLUCKED_STRING_H

#include <QWidget>
#include "app/gui/widget/instrument/string.h"
#include "string_synthesiser.h"

namespace app {
    class PluckedString : public QWidget {
    Q_OBJECT
    public:
        PluckedString(QWidget* widget);

        ~PluckedString();

        void paintEvent(QPaintEvent *event) override;

    private:
        QVector<String> string_lines_;
        QVector<StringSynthesiser> string_synths_;
    };
}

#endif //CHARACTER_PLUCKED_STRING_H
