//
// Created by wangrl2016 on 2023/7/17.
//

#ifndef CHARACTER_DECODER_BUFFER_H
#define CHARACTER_DECODER_BUFFER_H

namespace media {
    // A specialized buffer for interfacing with audio / video decoders.
    //
    // NOTE: It is illegal to call any method when end_of_stream() is true.
    class DecoderBuffer {

    };
}

#endif //CHARACTER_DECODER_BUFFER_H
