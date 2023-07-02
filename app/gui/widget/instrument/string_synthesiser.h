//
// Created by wangrl2016 on 2023/7/2.
//

#ifndef CHARACTER_STRING_SYNTHESISER_H
#define CHARACTER_STRING_SYNTHESISER_H

#include <vector>

namespace app {
    // A very basic generator of a simulated plucked string sound, implementing
    // the Karplus-Strong algorithms.
    class StringSynthesiser {
    public:
        StringSynthesiser(double sample_rate, double frequency);

        // Excite the simulated string by plucking it at a given position.
        //
        // @param pluck_position The position of the plucking, relative to the length
        //                       of the string, must between 0 and 1.
        void StringPlucked(float pluck_position);

        void GenerateAndAddData(float* out_buffer, int num_sample);

    private:
        void PrepareSynthesiserState(double sample_rate, double frequency);

        const double decay_ = 0.998;
        double amplitude_ = 0.0;

        std::vector<float> excitation_sample_, delay_line_;
        size_t pos_ = 0;
    };
}


#endif //CHARACTER_STRING_SYNTHESISER_H
