//
// Created by wangrl2016 on 2023/8/31.
//

#ifndef CHARACTER_PROPERTY_WIDGET_H
#define CHARACTER_PROPERTY_WIDGET_H

#include <QWidget>

namespace app {
    class PropertyWidget : public QWidget {
    Q_OBJECT
    public:
        PropertyWidget(QWidget* parent = nullptr);
    };
}


#endif //CHARACTER_PROPERTY_WIDGET_H
