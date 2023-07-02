//
// Created by wangrl2016 on 2023/6/26.
//

#ifndef CHARACTER_TRACK_H
#define CHARACTER_TRACK_H

#include <QObject>
#include <utility>

namespace app {
    class Clip;
    class TrackContainerModel;

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

        Track(TrackType type, TrackContainerModel* tc);

        static Track* Create(TrackType type, TrackContainerModel* tc);

        [[nodiscard]] TrackType type() const { return type_; }

        [[nodiscard]] bool solo() const { return solo_; }

        void set_solo(bool solo) { solo_ = solo; }

        [[nodiscard]] QString name() const { return name_; }

        void set_name(const QString& name) { name_ = name;}

    private:
        TrackType type_;
        TrackContainerModel* track_container_;
        QVector<Clip*> clip_vec_;

        bool solo_;
        QString name_;
    };
}

#endif //CHARACTER_TRACK_H
