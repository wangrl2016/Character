//
// Created by wangrl2016 on 2023/6/17.
//

#ifndef CHARACTER_PIANO_NODE_H
#define CHARACTER_PIANO_NODE_H

#include <juce_dsp/juce_dsp.h>
#include "module/audio_graph/processor_base.h"

namespace audio_graph {
    constexpr int kNumKey = 128;

    class PianoNode : public ProcessorBase {
    public:
        PianoNode();

        ~PianoNode();

        void prepareToPlay(double sample_rate,
                           int samples_per_block) override;

        void processBlock(juce::AudioSampleBuffer& buffer,
                          juce::MidiBuffer&) override;

        void reset() override;

        void TapDown(int pitch);

        void TapUp(int pitch);

    private:
        juce::dsp::Oscillator<float> oscillator_;

        bool is_down = false;
    };
}

#endif //CHARACTER_PIANO_NODE_H
