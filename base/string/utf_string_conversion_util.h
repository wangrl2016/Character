//
// Created by wangrl2016 on 2023/2/18.
//

#ifndef ONESTUDIO_UTF_STRING_CONVERSION_UTIL_H
#define ONESTUDIO_UTF_STRING_CONVERSION_UTIL_H

#include "third_party/icu/icu_utf.h"

namespace base {
    inline bool IsValidCodePoint(icu::UChar32 code_point) {
        // Excludes code points that are not Unicode scalar values, i.e.
        // surrogate code points ([0xD800, 0xDFFF]). Additionally, excludes
        // code points larger than 0x10FFFF (the highest codepoint allowed).
        // Non-characters and unassigned code points are allowed.
        // https://unicode.org/glossary/#unicode_scalar_value
        return (code_point >= 0 && code_point < 0xD800) ||
               (code_point > 0xDFFF && code_point <= 0x10FFFF);
    }

    inline bool IsValidCharacter(icu::UChar32 code_point) {
        // The 66 non-characters are allocated as follows:
        // a contiguous range of 32 non-characters: U+FDD0..U+FDEF in the
        // BMP (Basic Multilingual Plane)
        // the last two code points of the BMP, U+FFFE and U+FFFF
        // the last two code points of each of the 16 supplementary planes:
        // U+1FFFE, U+1FFFF, U+2FFFE, U+2FFFF, ... U+10FFFE, U+10FFFF
        // https://unicode.org/faq/private_use.html#nonchar1
        //
        // Note: Values between 0xD800 and 0xDFFF are specifically reserved for
        // use with UTF-16, and don't have any characters assigned to them.
        // https://www.ietf.org/rfc/rfc2781.txt
        //
        // Restricted the range of characters to 0000-10FFFF (the UTF-16 accessible range)
        // https://www.rfc-editor.org/rfc/rfc3629#page-11
        return (code_point >= 0 && code_point < 0xD800) ||
               (code_point > 0xDFFF && code_point < 0xFDD0) ||
               (code_point > 0xFDEF && code_point <= 0x10FFFF &&
                ((code_point & 0xFFFE) != 0xFFFE || (code_point & 0xFFFF) != 0xFFFF));
    }
}

#endif //ONESTUDIO_UTF_STRING_CONVERSION_UTIL_H
