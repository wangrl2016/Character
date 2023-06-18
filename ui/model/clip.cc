//
// Created by wangrl2016 on 2023/6/12.
//

#include "ui/model/track.h"
#include "ui/model/clip.h"

namespace ui {
    Clip::Clip(Track* track) : Model(track),
        track_(track) {

    }

    Clip::~Clip() = default;
}
