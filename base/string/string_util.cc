//
// Created by wangrl2016 on 2023/7/26.
//

#include "base/config/build_config.h"
#include "base/string/string_util.h"
#include "base/string/string_util_impl_helper.h"

namespace base {
    bool IsStringASCII(StringPiece str) {
        return internal::DoIsStringASCII(str.data(), str.length());
    }

    bool IsStringASCII(StringPiece16 str) {
        return internal::DoIsStringASCII(str.data(), str.length());
    }

#if defined(WCHAR_T_IS_UTF32)
    bool IsStringASCII(WStringPiece str) {
        return internal::DoIsStringASCII(str.data(), str.length());
    }
#endif
}
