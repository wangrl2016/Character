//
// Created by wangrl2016 on 2023/7/30.
//

#ifndef CHARACTER_STRING_CONCAT_H
#define CHARACTER_STRING_CONCAT_H

#include "base/string/string_piece.h"


namespace base {
    namespace internal {
        template<typename CharT, typename StringT>
        void StringAppendT(std::basic_string<CharT>& dest,
                           std::initializer_list<const StringT> pieces) {
            const size_t initial_size = dest.size();
            size_t total_size = initial_size;
            for (const auto& cur: pieces) {
                total_size += cur.size();
            }

            dest.resize(total_size);
            CharT* dest_char = &dest[initial_size];
            for (const auto& cur: pieces) {
                std::char_traits<CharT>::copy(dest_char, cur.data(), cur.size());
                dest_char += cur.size();
            }
        }

        template<typename StringT>
        auto StringConcatT(std::initializer_list<const StringT> pieces) {
            std::basic_string<typename StringT::value_type> result;
            StringAppendT(result, pieces);
            return result;
        }
    }

    // Initializer list forwards to the array version.
    inline std::string StringConcat(std::initializer_list<const StringPiece> pieces) {
        return internal::StringConcatT(pieces);
    }

    inline std::u16string StringConcat(std::initializer_list<const StringPiece16> pieces) {
        return internal::StringConcatT(pieces);
    }

    inline void StringAppend(std::string* dest,
                             std::initializer_list<const StringPiece> pieces) {
        internal::StringAppendT(*dest, pieces);
    }

    inline void StringAppend(std::u16string* dest,
                             std::initializer_list<const StringPiece16> pieces) {
        internal::StringAppendT(*dest, pieces);
    }
}

#endif //CHARACTER_STRING_CONCAT_H
