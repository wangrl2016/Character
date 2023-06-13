//
// Created by wangrl2016 on 2023/6/11.
//

#ifndef CHARACTER_TRACK_H
#define CHARACTER_TRACK_H

#include <QColor>
#include <QMutex>
#include "ui/model/model.h"
#include "ui/model/clip.h"

namespace ui {
    class TrackContainer;

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

        Track(TrackType type, TrackContainer* tc);

        ~Track() override;

        static Track* Create(TrackType type, TrackContainer* tc);

        Track* Clone();

        TrackType type() const {
            return type_;
        }

        void Lock() {
            processing_lock_.lock();
        }

        void Unlock() {
            processing_lock_.unlock();
        }

        bool TryLock() {
            return processing_lock_.tryLock();
        }

    signals:
        void DestroyedTrack();

        void NameChanged();

        void ClipAdded(Clip* clip);

        void ColorChanged();

    private:
        TrackContainer* track_container_;
        TrackType type_;
        QString name_;
        bool mute_;
        bool solo_;

        QColor color_;

        QMutex processing_lock_;

        QVector<std::shared_ptr<Clip>> clips;
    };
}

#endif //CHARACTER_TRACK_H
