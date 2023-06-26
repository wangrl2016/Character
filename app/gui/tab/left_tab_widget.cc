//
// Created by wangrl2016 on 2023/6/24.
//

#include "app/gui/tab/left_tab_widget.h"
#include "app/gui/widget/track_content_widget.h"
#include "app/gui/widget/track_setting_widget.h"

namespace app {
    constexpr int kDefaultWidgetWidth = 256;

    LeftTabWidget::LeftTabWidget(QWidget* parent) :
            TabWidget(parent) {
        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        setMinimumWidth(kDefaultWidgetWidth);
        // West indicates that the tab is on the left.
        setTabPosition(QTabWidget::West);
        setStyleSheet("QTabWidget {"
                      "    border: none;"
                      "}"
                      "QTabWidget::tab-bar {"
                      "    alignment: left;"
                      "}"
                      "QTabBar::tab {"
                      "    background: #EADDFF;"
                      "    border: none;"
                      "    padding: 2px;"
                      "}"
                      "QTabBar::tab::hover {"
                      "    background: #F6EDFF;"
                      "}"
                      "QTabBar::tab::selected {"
                      "    background: #D0BCFF;"
                      "}");

        addTab(new QWidget, QIcon(":tab/project"), "Project");
        addTab(new TrackSettingWidget(this), QIcon(":tab/track"), "Track");
        addTab(new QWidget, "Others");
    }
}
