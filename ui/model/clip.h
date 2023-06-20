//
// Created by wangrl2016 on 2023/6/12.
//

#ifndef CHARACTER_CLIP_H
#define CHARACTER_CLIP_H

#include <QColor>
#include "ui/model/model.h"

namespace ui {
    class Track;

    class ClipView;

    class TrackView;

    class Clip : public Model {
    Q_OBJECT
    public:
        explicit Clip(Track* track);

        ~Clip() override;

        [[nodiscard]] inline Track* track() const { return track_; }

        [[nodiscard]] inline const QString& name() const { return name_; }

        inline void set_name(const QString& name) {
            name_ = name;
            emit DataChanged();
        }

        [[nodiscard]] inline int start_pos() const { return start_pos_; }

        [[nodiscard]] inline int length() const { return length_; }

        [[nodiscard]] inline int end_position() const {
            return start_pos_ + length_;
        }

        [[nodiscard]] QColor color() const { return color_; }

        void set_color(const QColor& color) { color_ = color; }

        virtual void MovePosition(int pos);

        virtual void ChangeLength(int length);

        virtual ClipView* CreateView(TrackView* tv) = 0;

        // Return true if and only if a->start_pos() < b->start_pos().
        static bool ComparePosition(const Clip* a, const Clip* b);

        // Will copy the state of a clip to another clip.
        static void CopyStateTo(Clip* src, Clip* dst);

    signals:

        void LengthChanged();

        void PositionChanged();

        void DestroyClip();

        void ColorChanged();

    public slots:

        void ToggleMute();

    private:
        enum Action {
            kNoAction,
            kMove,
            kResize,
        };

        Track* track_;
        QString name_;

        int start_pos_;
        int length_;

        bool mute_;
        bool solo_;

        QColor color_;

        friend class ClipView;
    };
}

#endif //CHARACTER_CLIP_H
