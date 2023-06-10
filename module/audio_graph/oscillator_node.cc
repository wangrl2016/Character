//
// Created by wangrl2016 on 2023/6/10.
//

#include "module/audio_graph/oscillator_node.h"

namespace audio_graph {
    OscillatorNode::OscillatorNode() {
        oscillator_.setFrequency(440.0f);
        oscillator_.initialise([](float x) {
            return std::sin(x);
        });
    }

    void OscillatorNode::prepareToPlay(double sample_rate,
                                       int samples_per_block) {
        juce::dsp::ProcessSpec spec {
            sample_rate,
            static_cast<juce::uint32>(samples_per_block)};
        oscillator_.prepare(spec);
    }

    void OscillatorNode::processBlock(juce::AudioSampleBuffer& buffer,
                                      juce::MidiBuffer&) {
        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing<float> context(block);
        oscillator_.process(context);
    }

    void OscillatorNode::reset() {
        oscillator_.reset();
    }
}
