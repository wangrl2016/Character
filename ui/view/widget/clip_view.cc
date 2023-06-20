//
// Created by wr on 2023/6/21.
//

#include "clip_view.h"
#include "model_view.h"

namespace ui {
    ClipView::ClipView(Clip* clip, TrackView* tv) :
            SelectableObject(tv->TrackContentWidget()),
            ModelView(nullptr, this) {

    }
}