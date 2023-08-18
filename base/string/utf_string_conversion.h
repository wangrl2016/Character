//
// Created by wangrl2016 on 2023/2/18.
//

#ifndef ONESTUDIO_UTF_STRING_CONVERSION_H
#define ONESTUDIO_UTF_STRING_CONVERSION_H

#include "base/config/build_config.h"
#include "base/string/string_piece.h"

namespace base {
    // These convert between UTF-8, -16, and -32 strings. They are potentially slow,
    // so avoid unnecessary conversions. The low-level versions return a boolean
    // indicating whether the conversion was 100% valid. In this case, it will still
    // do the best it can put the result in the output buffer. The versions that
    // return strings ignore this error and just return the best conversion
    // possible.

    // Wide <=> UTF8

    bool WideToUTF8(const wchar_t* src, size_t src_len, std::string* output);

    std::string WideToUTF8(WStringPiece wide);

    bool UTF8ToWide(const char* src, size_t src_len, std::wstring* output);

    std::wstring UTF8ToWide(StringPiece utf8);

    // Wide <=> UTF16

    bool WideToUTF16(const wchar_t* src, size_t src_len, std::u16string* output);

    std::u16string WideToUTF16(WStringPiece wide);

    bool UTF16ToWide(const char16_t* src, size_t src_len, std::wstring* output);

    std::wstring UTF16ToWide(StringPiece16 utf16);

    // UTF8 <=> UTF16

    bool UTF8ToUTF16(const char* src, size_t src_len, std::u16string* output);

    std::u16string UTF8ToUTF16(StringPiece utf8);

    bool UTF16ToUTF8(const char16_t* src, size_t src_len, std::string* output);

    std::string UTF16ToUTF8(StringPiece16 utf16);

    std::u16string ASCIIToUTF16(StringPiece ascii);

    std::string UTF16ToASCII(StringPiece16 utf16);

#if defined(WCHAR_T_IS_UTF16)

    std::wstring ASCIIToWide(StringPiece ascii);

    std::string WideToASCII(WStringPiece wide);

#endif

}

#endif //ONESTUDIO_UTF_STRING_CONVERSION_H
