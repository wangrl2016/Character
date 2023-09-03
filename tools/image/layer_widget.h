//
// Created by wangrl2016 on 2023/9/1.
//

#ifndef CHARACTER_LAYER_WIDGET_H
#define CHARACTER_LAYER_WIDGET_H

#include <QListWidget>

namespace app {
    class LayerWidget : public QListWidget {
    Q_OBJECT
    public:
        LayerWidget(QWidget* parent = nullptr);
    };
}

#endif //CHARACTER_LAYER_WIDGET_H
