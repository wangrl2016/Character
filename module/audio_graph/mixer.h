//
// Created by wr on 2023/6/17.
//

#ifndef CHARACTER_MIXER_H
#define CHARACTER_MIXER_H


#include "module/audio_graph/processor_base.h"

namespace audio_graph {
    class Mixer : public ProcessorBase {
    public:
        Mixer();

        ~Mixer() override;

        void prepareToPlay(double sample_rate,
                           int samples_per_block) override;

        void processBlock(juce::AudioSampleBuffer& buffer,
                          juce::MidiBuffer&) override;

        void reset() override;
    };
}


#endif //CHARACTER_MIXER_H
