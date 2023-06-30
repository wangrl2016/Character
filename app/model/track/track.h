//
// Created by wangrl2016 on 2023/6/26.
//

#ifndef CHARACTER_TRACK_H
#define CHARACTER_TRACK_H

#include <QObject>

namespace app {
    class Clip;

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

    private:
        QVector<Clip*> clip_vec_;


    };
}

#endif //CHARACTER_TRACK_H
