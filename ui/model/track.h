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

        Track(TrackType type);

        ~Track() override;

        static std::shared_ptr<Track> Create(TrackType type);

        std::shared_ptr<Track> Clone();

        TrackType type() const {
            return type_;
        }

        void Lock() {
            processing_lock.lock();
        }

        void Unlock() {
            processing_lock.unlock();
        }

        bool TryLock() {
            return processing_lock.tryLock();
        }

    private:
        TrackType type_;
        QColor color_;

        QMutex processing_lock;

        QVector<std::shared_ptr<Clip>> clips;
    };
}

#endif //CHARACTER_TRACK_H
