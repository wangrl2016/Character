//
// Created by wangrl2016 on 2023/6/9.
//

#ifndef CHARACTER_AUDIO_CONTEXT_H
#define CHARACTER_AUDIO_CONTEXT_H

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_core/juce_core.h>

namespace audio_graph {
    class AudioContext {
    public:
        static AudioContext& Instance();

        bool Create();

        bool Start();

        bool Stop();

        bool Destroy();

        bool Exist();

        bool Seek();

        void StartBeat();

        void StopBeat();

        void Clear();

        std::string GetCurrentDefaultAudioDeviceName(bool is_input);

    private:
        AudioContext() = default;

        ~AudioContext() = default;

        // JUCE/examples/DemoRunner/Source/Demos/JUCEDemos.cpp
        bool InitAudioDeviceManager(int num_input_channels,
                                    int num_output_channels);

        bool InitAudioGraph();

        // https://docs.juce.com/master/tutorial_audio_processor_graph.html
        std::unique_ptr<juce::AudioDeviceManager> audio_device_manager_;
        std::unique_ptr<juce::AudioProcessorGraph> audio_processor_graph_;
        std::unique_ptr<juce::AudioProcessorPlayer> audio_processor_player_;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioContext)
    };
}

#endif //CHARACTER_AUDIO_CONTEXT_H
