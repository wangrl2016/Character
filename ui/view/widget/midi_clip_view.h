//
// Created by wr on 2023/6/20.
//

#ifndef CHARACTER_MIDI_CLIP_VIEW_H
#define CHARACTER_MIDI_CLIP_VIEW_H

#include "clip_view.h"

namespace ui {
    class MidiClip;

    class MidiClipView : public ClipView {
    Q_OBJECT
    public:
        MidiClipView(MidiClip* clip, TrackView* parent);

        MidiClipView()  = default;
    };
}


#endif //CHARACTER_MIDI_CLIP_VIEW_H
