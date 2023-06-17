//
// Created by wr on 2023/6/17.
//

#include <juce_dsp/juce_dsp.h>
#include "module/audio_graph/constant.h"
#include "module/audio_graph/mixer.h"

namespace audio_graph {

    Mixer::Mixer() : ProcessorBase(BusesProperties().
                    withInput("MixerInput",
                              juce::AudioChannelSet::discreteChannels(kMaxMixChannel))
                                           .withOutput("MixerOutput", juce::AudioChannelSet::stereo())) {

    }

    Mixer::~Mixer() = default;

    void Mixer::prepareToPlay(double sample_rate, int samples_per_block) {

    }

    void Mixer::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) {
        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing<float> context(block);

        auto&& in_block = context.getInputBlock();
        auto&& out_block = context.getOutputBlock();

        auto length = in_block.getNumSamples();
        auto channel_count = in_block.getNumChannels();

        // 0 + 2 + 4 + 6 + 8 -> 0
        // 1 + 3 + 5 + 7 + 9 -> 1
        // Not usesSeparateInputAndOutputBlocks
        for (size_t channel = kDefaultOutputChannelCount;
             channel < channel_count; channel++) {
            juce::FloatVectorOperations::add(
                    out_block.getChannelPointer(channel % kDefaultOutputChannelCount),
                    in_block.getChannelPointer(channel),
                    static_cast<int>(length));
        }
    }

    void Mixer::reset() {

    }
}
