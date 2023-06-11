//
// Created by wangrl2016 on 2023/6/11.
//

#ifndef CHARACTER_OSCILLATOR_H
#define CHARACTER_OSCILLATOR_H

namespace audio_graph {
    class Oscillator {
    public:
        enum WaveShape {
            kSineWave,
            kTriangleWave,
            kSawWave,
            kSquareWave,
        };

        enum ModulationAlgo {
            kPhaseModulation,
            kAmplitudeModulation,
        };

        Oscillator(const WaveShape wave_shape,
                   const ModulationAlgo modulation_algo,
                   const float freq,
                   const float sample_rate,
                   const float phase_offset,
                   const float volume);
    };
}


#endif //CHARACTER_OSCILLATOR_H
