//
// Created by wangrl2016 on 2023/6/10.
//

#ifndef CHARACTER_GAIN_NODE_H
#define CHARACTER_GAIN_NODE_H

#include <juce_dsp/juce_dsp.h>
#include "module/audio_graph/processor_base.h"

namespace audio_graph {
    class GainNode : public ProcessorBase {
    public:
        GainNode();

        void prepareToPlay(double sample_rate,
                           int samples_per_block) override;

        void processBlock(juce::AudioSampleBuffer& buffer,
                          juce::MidiBuffer&) override;

        void reset() override;

    private:
        juce::dsp::Gain<float> gain_;
    };
}

#endif //CHARACTER_GAIN_NODE_H
