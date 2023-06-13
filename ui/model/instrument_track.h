//
// Created by wangrl2016 on 2023/6/11.
//

#ifndef CHARACTER_INSTRUMENT_TRACK_H
#define CHARACTER_INSTRUMENT_TRACK_H

#include "ui/model/track.h"
#include "ui/model/track_container.h"

namespace ui {

    class InstrumentTrack : public Track {
    public:
        InstrumentTrack(TrackContainer* tc);

        ~InstrumentTrack() override;
    private:
        int base_note_;     // The "A4" or "440Hz" key (default 69)

        float volume_;
        float panning_;
    };
}

#endif //CHARACTER_INSTRUMENT_TRACK_H
