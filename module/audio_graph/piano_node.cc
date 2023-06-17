//
// Created by wangrl2016 on 2023/6/17.
//

#include "module/audio_graph/piano_node.h"

namespace audio_graph {
    PianoNode::PianoNode() {
        oscillator_.setFrequency(440.0f);
        oscillator_.initialise([](float x) {
            return std::sin(x);
        });
    }

    PianoNode::~PianoNode() = default;

    void PianoNode::prepareToPlay(double sample_rate, int samples_per_block) {
        juce::dsp::ProcessSpec spec {
                sample_rate,
                static_cast<juce::uint32>(samples_per_block)};
        oscillator_.prepare(spec);

        adsr_.setSampleRate(sample_rate);
        adsr_.setParameters(juce::ADSR::Parameters(
                0.1f, 0.1f, 1.0f, 0.1f));
    }

    void PianoNode::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) {
        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing<float> context(block);
        oscillator_.process(context);

        adsr_.applyEnvelopeToBuffer(buffer, 0, buffer.getNumSamples());
    }

    void PianoNode::reset() {
        oscillator_.reset();
    }

    void PianoNode::TapDown(int pitch) {
        adsr_.noteOn();
    }

    void PianoNode::TapUp(int pitch) {
        adsr_.noteOff();
    }
}
