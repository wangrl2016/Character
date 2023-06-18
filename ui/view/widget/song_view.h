//
// Created by wangrl2016 on 2023/6/13.
//

#ifndef CHARACTER_SONG_VIEW_H
#define CHARACTER_SONG_VIEW_H

#include <QScrollBar>
#include "ui/model/song.h"
#include "ui/view/widget/track_container_view.h"
#include "ui/view/widget/time_line_widget.h"

namespace ui {
    class SongView : public TrackContainerView {
    Q_OBJECT
    public:
        explicit SongView(Song* song);

        ~SongView() override = default;

    private:
        Song* song_;

        QScrollBar* left_right_scroll_;

        TimeLineWidget* time_line_;
    };
}

#endif //CHARACTER_SONG_VIEW_H
