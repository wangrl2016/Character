//
// Created by wangrl2016 on 2023/8/16.
//

#ifndef CHARACTER_DECODER_H
#define CHARACTER_DECODER_H

namespace media {
    // List of known AudioDecoder implementations, always add new
    // values to the end and do not reorder or delete value from this list.
    enum class AudioDecodeType : int {
        kUnknown = 0,       // Decoder name string is not recognized or n/a.
        kFFmpeg = 1,        // FFmpegAudioDecoder
    };
}

#endif //CHARACTER_DECODER_H
