//
// Created by wangrl2016 on 2023/6/10.
//

#ifndef CHARACTER_OSCILLATOR_NODE_H
#define CHARACTER_OSCILLATOR_NODE_H

#include <juce_dsp/juce_dsp.h>
#include "module/audio_graph/processor_base.h"

namespace audio_graph {
    class OscillatorNode : public ProcessorBase {
    public:
        OscillatorNode();

        void prepareToPlay(double sample_rate,
                           int samples_per_block) override;

        void processBlock(juce::AudioSampleBuffer& buffer,
                          juce::MidiBuffer&) override;

        void reset() override;

    private:
        juce::dsp::Oscillator<float> oscillator_;
    };
}

#endif //CHARACTER_OSCILLATOR_NODE_H
