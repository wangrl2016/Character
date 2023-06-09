//
// Created by wangrl2016 on 2023/6/9.
//

#ifndef CHARACTER_TRACK_H
#define CHARACTER_TRACK_H

namespace audio_graph {
    struct TrackID {
        explicit constexpr TrackID(int id) : track_id(id) {};
        int track_id;
    };

     constexpr TrackID kInvalidTrackID = TrackID(-1);

    class Track {
    public:
        enum TrackType {
            kInstrumentTrack,
            kPatternTrack,
        };

    private:
        TrackID id_;
    };
}

#endif //CHARACTER_TRACK_H
