//
// Created by wangrl2016 on 2023/6/24.
//

#ifndef CHARACTER_LEFT_TAB_WIDGET_H
#define CHARACTER_LEFT_TAB_WIDGET_H

#include "app/gui/tab/tab_widget.h"
#include "app/gui/widget/track_setting_widget.h"

namespace app {
    class LeftTabWidget : public TabWidget {
    Q_OBJECT
    public:
        LeftTabWidget(QWidget* parent = nullptr);

    private:
        TrackSettingWidget* track_setting_widget_;
    };
}

#endif //CHARACTER_LEFT_TAB_WIDGET_H
