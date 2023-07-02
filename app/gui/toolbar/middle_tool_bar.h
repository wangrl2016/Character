//
// Created by wangrl2016 on 2023/6/26.
//

#ifndef CHARACTER_MIDDLE_TOOL_BAR_H
#define CHARACTER_MIDDLE_TOOL_BAR_H

#include <QToolBar>
#include <QComboBox>

namespace app {
    class MiddleToolBar : public QToolBar {
    Q_OBJECT
    public:
        explicit MiddleToolBar(QWidget* parent = nullptr);

    private:
        QComboBox* instrument_combo_box_;

        QAction* minimize_action_;
        QAction* setting_action_;
    };
}

#endif //CHARACTER_MIDDLE_TOOL_BAR_H
