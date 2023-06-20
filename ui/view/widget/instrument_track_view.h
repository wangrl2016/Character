//
// Created by wr on 2023/6/20.
//

#ifndef CHARACTER_INSTRUMENT_TRACK_VIEW_H
#define CHARACTER_INSTRUMENT_TRACK_VIEW_H

#include "ui/view/widget/track_view.h"
#include "ui/model/instrument_track.h"

namespace ui {

    class TrackContainerView;

    class InstrumentTrackView : public TrackView {
    Q_OBJECT
    public:
        InstrumentTrackView(InstrumentTrack* it, TrackContainerView* tcv);
    };
}

#endif //CHARACTER_INSTRUMENT_TRACK_VIEW_H
