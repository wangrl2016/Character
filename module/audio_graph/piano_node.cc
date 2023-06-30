//
// Created by wangrl2016 on 2023/6/17.
//

#include "core/util/utility_function.h"
#include "module/audio_graph/piano_node.h"

namespace audio_graph {
    PianoNode::PianoNode() {
        for (int i = 0; i < kNumKeys; i++) {
            oscillator_[i].setFrequency(core::Pitch2Frequency(i));
            oscillator_[i].initialise([](float x) {
                return std::sin(x);
            });
        }
    }

    PianoNode::~PianoNode() = default;

    void PianoNode::prepareToPlay(double sample_rate, int samples_per_block) {
        juce::dsp::ProcessSpec spec{
                sample_rate,
                static_cast<juce::uint32>(samples_per_block)};

        for (int i = 0; i < kNumKeys; i++) {
            oscillator_[i].prepare(spec);

            adsr_[i].setSampleRate(sample_rate);
            adsr_[i].setParameters(juce::ADSR::Parameters(
                    0.1f, 0.1f, 1.0f, 0.1f));
        }
    }

    void PianoNode::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) {
        juce::AudioSampleBuffer temp_buffer(buffer.getNumChannels(),
                                            buffer.getNumSamples());
        for (int i = 0; i < kNumKeys; i++) {
            if (adsr_[i].isActive()) {
                temp_buffer.clear();
                juce::dsp::AudioBlock<float> block(temp_buffer);
                juce::dsp::ProcessContextReplacing<float> context(block);
                oscillator_[i].process(context);

                adsr_[i].applyEnvelopeToBuffer(temp_buffer,
                                               0,
                                               temp_buffer.getNumSamples());
                for (int ch = 0; ch < buffer.getNumChannels(); ch++) {
                    juce::FloatVectorOperations::add(buffer.getWritePointer(ch),
                                                     temp_buffer.getReadPointer(ch),
                                                     buffer.getNumSamples());
                }
            }
        }
    }

    void PianoNode::reset() {
        for (auto& osc: oscillator_) {
            osc.reset();
        }
    }

    void PianoNode::TapDown(int pitch) {
        if (0 <= pitch && pitch < kNumKeys) {
            adsr_[pitch].noteOn();
        }
    }

    void PianoNode::TapUp(int pitch) {
        if (0 <= pitch && pitch < kNumKeys) {
            adsr_[pitch].noteOff();
        }
    }
}
