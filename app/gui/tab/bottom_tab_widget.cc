//
// Created by wr on 2023/6/25.
//

#include "app/gui/tab/bottom_tab_widget.h"

namespace app {
    constexpr int kDefaultWidgetHeight = 256;
    BottomTabWidget::BottomTabWidget(QWidget* parent) :
            TabWidget(parent) {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        setMinimumHeight(kDefaultWidgetHeight);
        setTabPosition(QTabWidget::South);
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

        instrument_widget_ = new InstrumentWidget(this);
        addTab(instrument_widget_, QIcon(":tab/instrument"), tr("Instrument"));

    }
}
