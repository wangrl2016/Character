//
// Created by wangrl2016 on 2023/6/26.
//

#ifndef CHARACTER_CLIP_H
#define CHARACTER_CLIP_H

#include <QColor>
#include "app/model/model.h"

namespace app {
    class Track;

    class Clip : public Model {
    Q_OBJECT
    public:
        explicit Clip(Track* track);

        ~Clip() override;

        [[nodiscard]] inline Track* track() const { return track_; }

        inline void set_name(const QString& name) {
            name_ = name;
        }

        [[nodiscard]] inline const QString& name() const { return name_; }

        [[nodiscard]] inline int start_position() const {
            return start_position_;
        }

        [[nodiscard]] inline int end_position() const {
            return start_position_ + length_;
        }

        [[nodiscard]] inline int length() const {
            return length_;
        }

        [[nodiscard]] QColor color() const { return color_; }

    private:
        Track* track_;
        QString name_;
        QColor color_;

        int start_position_;
        int length_;
    };
}


#endif //CHARACTER_CLIP_H
