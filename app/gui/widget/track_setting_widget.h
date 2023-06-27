//
// Created by wr on 2023/6/22.
//

#ifndef CHARACTER_TRACK_SETTING_WIDGET_H
#define CHARACTER_TRACK_SETTING_WIDGET_H

#include <QWidget>
#include <QListView>

// https://doc.qt.io/qt-6/model-view-programming.html

namespace app {

    class TrackSettingWidget : public QListView {
    Q_OBJECT
    public:
        explicit TrackSettingWidget(QWidget* parent = nullptr);
    };
}


#endif //CHARACTER_TRACK_SETTING_WIDGET_H
