//
// Created by wangrl2016 on 2023/6/11.
//

#ifndef CHARACTER_INSTRUMENT_TRACK_H
#define CHARACTER_INSTRUMENT_TRACK_H

namespace ui {
    class InstrumentTrack {

    private:
        int base_note_;     // The "A4" or "440Hz" key (default 69)

        float volume_;
        float panning_;
    };
}

#endif //CHARACTER_INSTRUMENT_TRACK_H
