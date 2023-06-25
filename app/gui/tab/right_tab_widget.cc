//
// Created by wangrl2016 on 2023/6/26.
//

#include "app/gui/tab/right_tab_widget.h"

namespace app {
    constexpr int kDefaultWidgetWidth = 256;

    RightTabWidget::RightTabWidget(QWidget* parent) :
            TabWidget(parent) {
        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        setMinimumWidth(kDefaultWidgetWidth);
        setTabPosition(QTabWidget::East);
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
                      "}"
                      );

        addTab(new QWidget, "Tab1");
        addTab(new QWidget, "Tab2");
        addTab(new QWidget, "Tab3");

    }
}