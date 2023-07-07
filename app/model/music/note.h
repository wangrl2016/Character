//
// Created by wangrl2016 on 2023/6/10.
//

#ifndef CHARACTER_NOTE_H
#define CHARACTER_NOTE_H

#include <QString>
#include "core/math/music_constant.h"

namespace app {
    class Note {
    public:
        Note(int pos, int length, int pitch,
             float volume = 1.0f, float panning = 0.0f,
             QString pronouncing = "", QString lyric = "");

        Note(const Note& note);

        ~Note();

        void set_length(int length) { length_ = length; }

        void set_pos(int pos) { pos_ = pos; }

        void set_pitch(int pitch) { pitch_ = pitch; }

        void set_volume(float volume) { volume_ = volume; }

        void set_panning(float panning) { panning_ = panning; }

        [[nodiscard]] inline int pos() const { return pos_; }

        [[nodiscard]] inline int length() const { return length_; }

        [[nodiscard]] inline int end_pos() const { return pos_ + length_; }

        [[nodiscard]] inline int pitch() const { return pitch_; }

        [[nodiscard]] inline float volume() const { return volume_; }

        [[nodiscard]] inline float panning() const { return panning_; }

        static inline bool LessThan(const Note* lhs, const Note* rhs) {
            // function to compare two notes
            if (lhs->pos() < rhs->pos()) {
                return true;
            } else if (lhs->pos() > rhs->pos()) {
                return false;
            }
            return lhs->pitch() > rhs->pitch();
        }

    private:
        int pitch_;
        float volume_;
        float panning_;
        int pos_;
        int length_;

        QString pronouncing_;
        QString lyric_;
    };
}

#endif //CHARACTER_NOTE_H
