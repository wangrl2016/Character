//
// Created by wangrl2016 on 2023/6/12.
//

#include "ui/model/track.h"
#include "ui/model/clip.h"

namespace ui {
    Clip::Clip(Track* t) : Model(t),
        track_(t),
        start_pos_(0),
        length_(0),
        mute_(false),
        solo_(false),
        color_(128, 128, 128) {
        if (track()) {
            track()->AddClip(this);
        }
    }

    Clip::~Clip() = default;
}
