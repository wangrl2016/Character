//
// Created by admin on 2023/6/9.
//

#ifndef CHARACTER_PROCESSOR_BASE_H
#define CHARACTER_PROCESSOR_BASE_H

#include <juce_audio_processors/juce_audio_processors.h>

namespace audio_graph {
    class ProcessorBase : public juce::AudioProcessor {
    public:
        ProcessorBase() : AudioProcessor(
                BusesProperties()
                        .withInput("Input", juce::AudioChannelSet::stereo())
                        .withOutput("Output", juce::AudioChannelSet::stereo())) {

        }

        ProcessorBase(const BusesProperties& layouts) : AudioProcessor(layouts) {}

        void prepareToPlay(double, int) override {}

        void releaseResources() override {}

        void processBlock(juce::AudioSampleBuffer&, juce::MidiBuffer&) override {}

        juce::AudioProcessorEditor* createEditor() override { return nullptr; }

        bool hasEditor() const override { return false; }

        const juce::String getName() const override { return {}; }

        bool acceptsMidi() const override { return false; }

        bool producesMidi() const override { return false; }

        double getTailLengthSeconds() const override { return 0; }

        int getNumPrograms() override { return 0; }

        int getCurrentProgram() override { return 0; }

        void setCurrentProgram(int) override {}

        const juce::String getProgramName(int) override { return {}; }

        void changeProgramName(int, const juce::String&) override {}

        void getStateInformation(juce::MemoryBlock&) override {}

        void setStateInformation(const void*, int) override {}

        void StartBeat() { beat_ = true; }

        void StopBeat() { beat_ = false; }

    protected:
        bool beat_ = false;

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProcessorBase)
    };
}

#endif //CHARACTER_PROCESSOR_BASE_H
