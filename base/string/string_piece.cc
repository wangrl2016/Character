//
// Created by wangrl2016 on 2023/7/26.
//

#include "base/string/string_piece.h"
#include "base/string/utf_string_conversion.h"

namespace base {
    std::ostream& operator<<(std::ostream& o, StringPiece piece) {
        o.write(piece.data(), static_cast<std::streamsize>(piece.size()));
        return o;
    }

    std::ostream& operator<<(std::ostream& o, StringPiece16 piece) {
        return o << UTF16ToUTF8(piece);
    }

    std::ostream& operator<<(std::ostream& o, WStringPiece piece) {
        return o << WideToUTF8(piece);
    }
}


