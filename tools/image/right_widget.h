//
// Created by wangrl2016 on 2023/9/3.
//

#ifndef CHARACTER_RIGHT_WIDGET_H
#define CHARACTER_RIGHT_WIDGET_H

#include <QWidget>
#include "tools/image/layer_widget.h"
#include "tools/image/property_widget.h"

namespace app {
    class RightWidget : public QWidget {
    Q_OBJECT
    public:
        RightWidget(QWidget* parent = nullptr);

    private:
        LayerWidget* layer_widget_;
        PropertyWidget* property_widget_;
    };
}


#endif //CHARACTER_RIGHT_WIDGET_H
