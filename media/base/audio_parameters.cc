//
// Created by wangrl2016 on 2023/6/2.
//

#include "media/base/audio_parameters.h"

namespace media {
    AudioParameters::AudioParameters(int sample_rate,
                                     int channel_count,
                                     AVSampleFormat sample_format)
            : sample_rate_(sample_rate),
              channel_count_(channel_count),
              sample_format_(sample_format) {}

    void AudioParameters::SetParams(int sample_rate,
                                    int channel_count,
                                    AVSampleFormat sample_format) {
        sample_rate_ = sample_rate;
        channel_count_ = channel_count;
        sample_format_ = sample_format;
    }

    bool AudioParameters::IsValid() const {
        return sample_rate_ > 0 &&
               channel_count_ > 0 &&
               sample_format_ != AV_SAMPLE_FMT_NONE;
    }
}
