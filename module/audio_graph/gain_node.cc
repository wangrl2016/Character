//
// Created by wangrl2016 on 2023/6/10.
//

#include "module/audio_graph/constant.h"
#include "module/audio_graph/gain_node.h"
#include "audio_context.h"

namespace audio_graph {
    GainNode::GainNode() {
        gain_.setGainDecibels(-6.0f);
    }

    void GainNode::prepareToPlay(double sample_rate,
                                 int samples_per_block) {
        juce::dsp::ProcessSpec spec {
            sample_rate,
            static_cast<juce::uint32>(samples_per_block),
            kDefaultOutputChannelCount
        };
        gain_.prepare(spec);
    }

    void GainNode::processBlock(juce::AudioSampleBuffer& buffer,
                                juce::MidiBuffer&) {
        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing<float> context(block);
        gain_.process(context);

        if (beat_) {
            play_index_ += buffer.getNumSamples();
            AudioContext::Instance()->OnPlayProgressCallback(play_index_);
        }
    }

    void GainNode::reset() {
        gain_.reset();
    }
}
