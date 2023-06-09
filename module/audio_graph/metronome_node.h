//
// Created by wangrl2016 on 2023/6/9.
//

#ifndef CHARACTER_METRONOME_NODE_H
#define CHARACTER_METRONOME_NODE_H

#include "module/audio_graph/processor_base.h"

namespace audio_graph {
    class MetronomeNode : public ProcessorBase {
    public:
        void prepareToPlay(double, int) override;

        void processBlock(juce::AudioSampleBuffer&, juce::MidiBuffer&) override;

        void reset() override;
    };
}

#endif //CHARACTER_METRONOME_NODE_H
