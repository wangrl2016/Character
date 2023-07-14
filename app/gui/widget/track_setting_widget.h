//
// Created by wr on 2023/6/22.
//

#ifndef CHARACTER_TRACK_SETTING_WIDGET_H
#define CHARACTER_TRACK_SETTING_WIDGET_H

#include <QWidget>
#include <QTableView>
#include "app/presenter/track_container_view.h"
#include "app/gui/widget/track_delegate.h"

// https://doc.qt.io/qt-6/model-view-programming.html

namespace app {
    class TrackSettingWidget : public QTableView,
            public TrackContainerView {
    Q_OBJECT
    public:
        explicit TrackSettingWidget(QWidget* parent = nullptr);

    private:
        QWidget* top_widget_;
        TrackDelegate* track_delegate_;
    };
}

#endif //CHARACTER_TRACK_SETTING_WIDGET_H
