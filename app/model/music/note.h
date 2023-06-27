//
// Created by wangrl2016 on 2023/6/10.
//

#ifndef CHARACTER_NOTE_H
#define CHARACTER_NOTE_H

#include <QString>
#include "core/math/music_constant.h"

namespace ui {
    class Note {
    public:
        Note(int pos, int length, int key,
             float volume = 1.0f, float panning = 0.0f,
             QString pronouncing = "", QString lyric = "");

        ~Note();

        inline void set_selected(const bool selected) { selected_ = selected; }

        inline void set_old_key(const int old_key) { old_key_ = old_key; }

        inline void set_old_pos(const int old_pos) { old_pos_ = old_pos; }

        inline void set_old_length(const int old_length) {
            old_length_ = old_length;
        }

        inline void set_is_playing(bool is_playing) {
            is_playing_ = is_playing;
        }

        void set_length(int length) { length_ = length; }

        void set_pos(int pos) { pos_ = pos; }

        void set_key(int key) { key_ = key; }

        virtual void set_volume(float volume) { volume_ = volume; }

        virtual void set_panning(float panning) { panning_ = panning; }

        [[nodiscard]] inline bool selected() const { return selected_; }

        [[nodiscard]] inline int old_key() const { return old_key_; }

        [[nodiscard]] inline int old_pos() const { return old_pos_; }

        [[nodiscard]] inline int old_length() const { return old_length_; }

        [[nodiscard]] inline bool is_playing() const { return is_playing_; }

        [[nodiscard]] inline int pos() const { return pos_; }

        [[nodiscard]] inline int length() const { return length_; }

        [[nodiscard]] inline int end_pos() const { return pos_ + length_; }

        [[nodiscard]] inline int key() const { return key_; }

        [[nodiscard]] inline float volume() const { return volume_; }

        [[nodiscard]] inline float panning() const { return panning_; }

        static inline bool LessThan(const Note* lhs, const Note* rhs) {
            // function to compare two notes
            if (lhs->pos() < rhs->pos()) {
                return true;
            } else if (lhs->pos() > rhs->pos()) {
                return false;
            }
            return lhs->key() > rhs->key();
        }

    private:
        int key_;
        float volume_;
        float panning_;
        int pos_;
        int length_;

        QString pronouncing_;
        QString lyric_;

        // for piano roll editing
        bool selected_;
        int old_key_;
        int old_pos_;
        int old_length_;
        bool is_playing_;
    };
}

#endif //CHARACTER_NOTE_H
