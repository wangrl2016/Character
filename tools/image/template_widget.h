//
// Created by admin on 2023/8/30.
//

#ifndef CHARACTER_TEMPLATE_WIDGET_H
#define CHARACTER_TEMPLATE_WIDGET_H

#include <QWidget>

namespace app {
    class TemplateWidget : public QWidget {
    Q_OBJECT
    public:
        TemplateWidget(QWidget* parent = nullptr);
    };
}

#endif //CHARACTER_TEMPLATE_WIDGET_H
