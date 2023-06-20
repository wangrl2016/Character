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

    class TrackContainerView;

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

        virtual TrackView* CreateView(TrackContainerView* view) = 0;

        virtual Clip* CreateClip(int pos) = 0;

        Clip* AddClip(Clip* clip);

        void RemoveClip(Clip* clip);

        void DeleteClips();

        int NumOfClips();

        Clip* GetClip(int clip_num);

        int GetClipNum(const Clip* clip);

        void InsertBar(int pos);

        void RemoveBar(int pos);

        // return length of bar
        int Length() const;

        virtual const QString& name() const {
            return name_;
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

        QColor color() { return color_; }

        bool mute() { return mute_; }

    signals:

        void DestroyedTrack();

        void NameChanged();

        void ClipAdded(Clip* clip);

        void ColorChanged();

    public slots:

        void ToggleSolo();

    private:
        TrackContainer* track_container_;
        TrackType type_;
        QString name_;
        int height_;
        bool mute_;
        bool solo_;
        QColor color_;

        QMutex processing_lock_;
        QVector<std::shared_ptr<Clip>> clips;

        friend class TrackView;
    };
}

#endif //CHARACTER_TRACK_H
