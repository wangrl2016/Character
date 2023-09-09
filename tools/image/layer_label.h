//
// Created by wr on 2023/9/9.
//

#ifndef CHARACTER_LAYER_LABEL_H
#define CHARACTER_LAYER_LABEL_H

#include <QWidget>
#include <QLabel>

namespace app {
    class LayerLabel : public QWidget {
    Q_OBJECT
    public:
        LayerLabel(QWidget* parent = nullptr);

    private:
        QLabel* layer_label_;
    };
}

#endif //CHARACTER_LAYER_LABEL_H
