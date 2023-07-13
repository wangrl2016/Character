//
// Created by wangrl2016 on 2023/6/21.
//

#ifndef CHARACTER_TOP_TOOL_BAR_H
#define CHARACTER_TOP_TOOL_BAR_H

#include <QToolBar>

namespace app {
    class TopToolBar : public QToolBar {
    Q_OBJECT
    public:
        TopToolBar(QWidget* parent);

    public slots:

        void Export();

    private:
        QAction* fast_rewind_action_;
        QAction* fast_forward_action_;
        QAction* skip_previous_action_;
        QAction* play_arrow_action_;
        QAction* pause_action_;

        QAction* export_action_;
        QAction* account_circle_action_;
    };
}


#endif //CHARACTER_TOP_TOOL_BAR_H
