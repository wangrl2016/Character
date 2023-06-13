//
// Created by wangrl2016 on 2023/6/13.
//

#include "ui/view/widget/song_view.h"

namespace ui {
    SongView::SongView(Song* song) :
            TrackContainerView(song),
            song_(song) {}
}