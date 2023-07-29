//
// Created by wangrl2016 on 2023/7/26.
//

#ifndef CHARACTER_STRING_UTIL_H
#define CHARACTER_STRING_UTIL_H

#include "base/string/string_piece.h"

namespace base {
    // character tabulation, line tabulation, form feed (FF), space
    #define WHITESPACE_ASCII_NO_CR_LF 0x09, 0x0B, 0x0C, 0x20

    // Comment to make clang-format linebreak
    // line feed (LF), carriage return (CR)
    #define WHITE_SPACE_ASCII WHITESPACE_ASCII_NO_CR_LF, 0x0A, 0x0D

    const char kWhitespaceASCII[] = {WHITE_SPACE_ASCII, 0};

    const char16_t kWhitespaceASCIIAs16[] = {WHITE_SPACE_ASCII, 0};

    const char kUTF8ByteOrderMark[] = "\xEF\xBB\xBF";

    // ASCII-specific tolower. The standard library's tolower is locale sensitive,
    // so we don't want to use it here.
    template<typename CharT,
            typename =std::enable_if_t<std::is_integral<CharT>::value>>
    constexpr CharT ToLowerASCII(CharT c) {
        return (c >= 'A' && c <= 'Z') ? (c + ('a' - 'A')) : c;
    }

    bool IsStringASCII(StringPiece str);

    bool IsStringASCII(StringPiece16 str);

#if defined(WCHAR_T_IS_UTF32)
    bool IsStringASCII(WStringPiece str);
#endif

    // Indicates case sensitivity of comparisons. Only ASCII case insensitivity
    // is supported. Full Unicode case-insensitive conversions would need to go
    // to use ICU.
    enum class CompareCase {
        kSensitive,
        kInsensitiveASCII,
    };

    bool StartsWith(StringPiece str,
                    StringPiece search_for,
                    CompareCase case_sensitivity = CompareCase::kSensitive);

    bool StartsWith(StringPiece16 str,
                    StringPiece16 search_for,
                    CompareCase case_sensitivity = CompareCase::kSensitive);

    bool EndsWith(StringPiece str,
                  StringPiece search_for,
                  CompareCase case_sensitivity = CompareCase::kSensitive);

    bool EndsWith(StringPiece16 str,
                  StringPiece16 search_for,
                  CompareCase case_sensitivity = CompareCase::kSensitive);
}

#endif //CHARACTER_STRING_UTIL_H
