//
// Created by wangrl2016 on 2023/7/26.
//

#ifndef CHARACTER_STRING_PIECE_H
#define CHARACTER_STRING_PIECE_H

#include <ostream>
#include <string_view>

namespace base {
    using StringPiece = std::basic_string_view<char>;
    using StringPiece16 = std::basic_string_view<char16_t>;
    using WStringPiece = std::basic_string_view<wchar_t>;

    std::ostream& operator<<(std::ostream& o, StringPiece piece);

    std::ostream& operator<<(std::ostream& o, StringPiece16 piece);

    std::ostream& operator<<(std::ostream& o, WStringPiece piece);
}

#endif //CHARACTER_STRING_PIECE_H
