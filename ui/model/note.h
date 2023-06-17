//
// Created by wangrl2016 on 2023/6/10.
//

#ifndef CHARACTER_NOTE_H
#define CHARACTER_NOTE_H

#include "core/math/constant.h"

namespace ui {
    class Note {
    public:
        Note(int pos, int length,
             int key, float volume, float panning);

        Note(const Note& note);

        ~Note();

        inline void set_selected(const bool selected) { selected_ = selected; }

        inline void set_old_key(const int old_key) { old_key_ = old_key; }

        inline void set_old_pos(const int old_pos) { old_pos_ = old_pos; };

        inline void set_old_length(const int old_length) {
            old_length_ = old_length;
        }

        inline void set_is_playing(const bool is_playing) {
            is_playing_ = is_playing;
        }

        void set_length(const float length) { length_ = length; }

        void set_pos(const int pos) { pos_ = pos; }

        void set_key(const int key) { key_ = key; }

        virtual void set_volume(float volume) { volume_ = volume; }

        virtual void set_panning(float panning) { panning_ = panning; }

        inline bool selected() const { return selected_; }

        inline int old_key() const { return old_key_; }

        inline int old_pos() const { return old_pos_; }

        inline int old_length() const { return old_length_; }

        inline bool is_playing() const { return is_playing_; }

        inline int pos() const { return pos_; }

        inline int length() const { return length_; }

        inline int end_pos() const { return pos_ + length_; }

        inline int key() const { return key_; }

        inline float volume() const { return volume_; }

        inline float panning() const { return panning_; }

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

        // for piano roll editing
        bool selected_;
        int old_key_;
        int old_pos_;
        int old_length_;
        bool is_playing_;
    };
}


#endif //CHARACTER_NOTE_H
