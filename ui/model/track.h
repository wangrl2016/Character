//
// Created by wangrl2016 on 2023/6/11.
//

#ifndef CHARACTER_TRACK_H
#define CHARACTER_TRACK_H

#include "ui/model/model.h"

namespace ui {
    constexpr int kMinTrackHeight = 32;
    constexpr int kDefaultTrackHeight = 32;

    class Track : public Model {
    Q_OBJECT
    public:
        enum TrackType {
            kInstrumentTrack,
            kPatternTrack,
            kSampleTrack,
            kTrackCount,
        };
    };
}

#endif //CHARACTER_TRACK_H
