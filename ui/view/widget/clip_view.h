//
// Created by wr on 2023/6/21.
//

#ifndef CHARACTER_CLIP_VIEW_H
#define CHARACTER_CLIP_VIEW_H

#include "ui/view/widget/model_view.h"
#include "selectable_object.h"

namespace ui {
    class Clip;
    class TrackView;

    class ClipView : public SelectableObject, public ModelView {
    Q_OBJECT
    public:
        ClipView(Clip* clip, TrackView* tv);
    };
}


#endif //CHARACTER_CLIP_VIEW_H
