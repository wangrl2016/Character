//
// Created by wangrl2016 on 2023/6/26.
//

#ifndef CHARACTER_TRACK_H
#define CHARACTER_TRACK_H

#include <QObject>

namespace app {
    class Clip;
    class TrackContainer;

    class Track : public QObject {
    Q_OBJECT
    public:
        enum TrackType {
            kInstrumentTrack,
            kSampleTrack,
            kPictureTrack,
            kVideoTrack,
            kTrackCount,
        };

        Track(TrackType type, TrackContainer* tc);

        static Track* Create(TrackType type, TrackContainer* tc);

        [[nodiscard]] TrackType type() const { return type_; }

        [[nodiscard]] bool solo() const { return solo_; }

        void set_solo(bool solo) { solo_ = solo; }

    private:
        TrackType type_;
        TrackContainer* track_container_;
        QVector<Clip*> clip_vec_;

        bool solo_;
    };
}

#endif //CHARACTER_TRACK_H
