//
// Created by wangrl2016 on 2023/6/12.
//

#ifndef CHARACTER_CLIP_H
#define CHARACTER_CLIP_H

#include <QColor>
#include "ui/model/model.h"

namespace ui {
    class Track;

    class Clip : public Model {
    Q_OBJECT
    public:
        explicit Clip(Track* track);

        ~Clip() override;

        inline Track* track() const { return track_; }

        inline const QString& name() const { return name_; }

        inline void set_name(const QString& name) {
            name_ = name;
            emit DataChanged();
        }

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

    };
}

#endif //CHARACTER_CLIP_H
