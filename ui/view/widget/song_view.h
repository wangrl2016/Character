//
// Created by wangrl2016 on 2023/6/13.
//

#ifndef CHARACTER_SONG_VIEW_H
#define CHARACTER_SONG_VIEW_H

#include "ui/model/song.h"
#include "ui/view/widget/track_container_view.h"

namespace ui {
    class SongView : public TrackContainerView {
    Q_OBJECT
    public:
        SongView(Song* song);

        ~SongView() override = default;




    private:
        Song* song_;
    };
}

#endif //CHARACTER_SONG_VIEW_H
