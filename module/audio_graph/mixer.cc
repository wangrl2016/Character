//
// Created by wr on 2023/6/17.
//

#include <juce_dsp/juce_dsp.h>
#include "module/audio_graph/constant.h"
#include "module/audio_graph/mixer.h"

namespace audio_graph {
    Mixer::Mixer() = default;

    Mixer::~Mixer() = default;

    void Mixer::prepareToPlay(double sample_rate, int samples_per_block) {}

    void Mixer::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) {}

    void Mixer::reset() {}
}
