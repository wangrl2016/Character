//
// Created by wangrl2016 on 2023/6/10.
//

#include <QtGlobal>
#include <utility>
#include "app/model/music/note.h"

namespace app {
    Note::Note(int pos, int length,
               int key, float volume,
               float panning, QString pronouncing,
               QString lyric) :
            pitch_(qBound(0, key, kNumKeys)),
            volume_(volume),
            panning_(panning),
            pos_(pos),
            length_(length),
            pronouncing_(std::move(pronouncing)),
            lyric_(std::move(lyric)) {

    }

    Note::Note(const Note& note) :
            pitch_(note.pitch_),
            volume_(note.volume_),
            panning_(note.panning_),
            pos_(note.pos_),
            length_(note.length_),
            pronouncing_(note.pronouncing_),
            lyric_(note.lyric_) {
    }

    Note::~Note() = default;
}