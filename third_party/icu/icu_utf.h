//
// Created by wangrl2016 on 2023/7/28.
//

#ifndef CHARACTER_ICU_UTF_H
#define CHARACTER_ICU_UTF_H

#include <cstdint>

namespace icu {
    // common/unicode/umachine.h

    /**
     * Define UChar32 as a type for single Unicode code points.
     * UChar32 is a signed 32-bit integer (same as int32_t).
     *
     * The Unicode code point range is 0..0x10ffff.
     * All other values (negative or >=0x110000) are illegal as Unicode code points.
     * They may be used as sentinel values to indicate "done", "error"
     * or similar non-code point conditions.
     *
     * Before ICU 2.4 (Jitterbug 2146), UChar32 was defined
     * to be wchar_t if that is 32 bits wide (wchar_t may be signed or unsigned)
     * or else to be uint32_t.
     * That is, the definition of UChar32 was platform-dependent.
     *
     * @see U_SENTINEL
     * @stable ICU 2.4
     */
    typedef int32_t UChar32;

    /**
     * This value is intended for sentinel values for APIs that
     * (take or) return single code points (UChar32).
     * It is outside of the Unicode code point range 0..0x10ffff.
     *
     * For example, a "done" or "error" value in a new API
     * could be indicated with U_SENTINEL.
     *
     * ICU APIs designed before ICU 2.4 usually define service-specific "done"
     * values, mostly 0xffff.
     * Those may need to be distinguished from
     * actual U+ffff text contents by calling functions like
     * CharacterIterator::hasNext() or UnicodeString::length().
     *
     * @return -1
     * @see UChar32
     * @stable ICU 2.4
     */
    #define U_SENTINEL (-1)

    // Before ICU 65, function-like, multi-statement ICU macros were just defined as
    // series of statements wrapped in { } blocks and the caller could choose to
    // either treat them as if they were actual functions and end the invocation
    // with a trailing ; creating an empty statement after the block or else omit
    // this trailing ; using the knowledge that the macro would expand to { }.
    //
    // But doing so doesn't work well with macros that look like functions and
    // compiler warnings about empty statements (ICU-20601) and ICU 65 therefore
    // switches to the standard solution of wrapping such macros in do { } while.
    //
    // This will however break existing code that depends on being able to invoke
    // these macros without a trailing ; so to be able to remain compatible with
    // such code the wrapper is itself defined as macros so that it's possible to
    // build ICU 65 and later with the old macro behaviour, like this:
    //
    // export CPPFLAGS='-DUPRV_BLOCK_MACRO_BEGIN="" -DUPRV_BLOCK_MACRO_END=""'
    // runConfigureICU ...
    //

    /**
     * \def UPRV_BLOCK_MACRO_BEGIN
     * Defined as the "do" keyword by default.
     * @internal
     */
    #ifndef UPRV_BLOCK_MACRO_BEGIN
        #define UPRV_BLOCK_MACRO_BEGIN do
    #endif

    /**
     * \def UPRV_BLOCK_MACRO_END
     * Defined as "while (false)" by default.
     * @internal
     */
    #ifndef UPRV_BLOCK_MACRO_END
        #define UPRV_BLOCK_MACRO_END while (false)
    #endif

    // common/unicode/utf.h

    /**
     * Is this code point a surrogate (U+d800..U+dfff)?
     * @param c 32-bit code point
     * @return true or false
     * @stable ICU 2.4
     */
    #define U_IS_SURROGATE(c) (((c)&0xfffff800)==0xd800)

    // common/unicode/utf8.h

    /**
     * Does this code unit (byte) encode a code point by itself (US-ASCII 0..0x7f)?
     * @param c 8-bit code unit (byte)
     * @return true or false
     * @stable ICU 2.4
     */
    #define U8_IS_SINGLE(c) (((c)&0x80)==0)

    /**
     * Internal bit vector for 3-byte UTF-8 validity check, for use in U8_IS_VALID_LEAD3_AND_T1.
     * Each bit indicates whether one lead byte + first trail byte pair starts a valid sequence.
     * Lead byte E0..EF bits 3..0 are used as byte index,
     * first trail byte bits 7..5 are used as bit index into that byte.
     * @see U8_IS_VALID_LEAD3_AND_T1
     * @internal
     */
    #define U8_LEAD3_T1_BITS "\x20\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x10\x30\x30"

    /**
     * Internal bit vector for 4-byte UTF-8 validity check, for use in U8_IS_VALID_LEAD4_AND_T1.
     * Each bit indicates whether one lead byte + first trail byte pair starts a valid sequence.
     * First trail byte bits 7..4 are used as byte index,
     * lead byte F0..F4 bits 2..0 are used as bit index into that byte.
     * @see U8_IS_VALID_LEAD4_AND_T1
     * @internal
     */
    #define U8_LEAD4_T1_BITS "\x00\x00\x00\x00\x00\x00\x00\x00\x1E\x0F\x0F\x0F\x00\x00\x00\x00"

    /** @internal */
    #define U8_INTERNAL_NEXT_OR_SUB(s, i, length, c, sub) UPRV_BLOCK_MACRO_BEGIN { \
        (c)=(uint8_t)(s)[(i)++]; \
        if(!U8_IS_SINGLE(c)) { \
            uint8_t __t = 0; \
            if((i)!=(length) && \
                /* fetch/validate/assemble all but last trail byte */ \
                ((c)>=0xe0 ? \
                    ((c)<0xf0 ?  /* U+0800..U+FFFF except surrogates */ \
                        U8_LEAD3_T1_BITS[(c)&=0xf]&(1<<((__t=(s)[i])>>5)) && \
                        (__t&=0x3f, 1) \
                    :  /* U+10000..U+10FFFF */ \
                        ((c)-=0xf0)<=4 && \
                        U8_LEAD4_T1_BITS[(__t=(s)[i])>>4]&(1<<(c)) && \
                        ((c)=((c)<<6)|(__t&0x3f), ++(i)!=(length)) && \
                        (__t=(s)[i]-0x80)<=0x3f) && \
                    /* valid second-to-last trail byte */ \
                    ((c)=((c)<<6)|__t, ++(i)!=(length)) \
                :  /* U+0080..U+07FF */ \
                    (c)>=0xc2 && ((c)&=0x1f, 1)) && \
                /* last trail byte */ \
                (__t=(s)[i]-0x80)<=0x3f && \
                ((c)=((c)<<6)|__t, ++(i), 1)) { \
            } else { \
                (c)=(sub);  /* ill-formed*/ \
            } \
        } \
    } UPRV_BLOCK_MACRO_END

    /**
     * Get a code point from a string at a code point boundary offset,
     * and advance the offset to the next code point boundary.
     * (Post-incrementing forward iteration.)
     * "Safe" macro, checks for illegal sequences and for string boundaries.
     *
     * The length can be negative for a NUL-terminated string.
     *
     * The offset may point to the lead byte of a multi-byte sequence,
     * in which case the macro will read the whole sequence.
     * If the offset points to a trail byte or an illegal UTF-8 sequence, then
     * c is set to a negative value.
     *
     * @param s const uint8_t * string
     * @param i int32_t string offset, must be i<length
     * @param length int32_t string length
     * @param c output UChar32 variable, set to <0 in case of an error
     * @see U8_NEXT_UNSAFE
     * @stable ICU 2.4
     */
    #define U8_NEXT(s, i, length, c) U8_INTERNAL_NEXT_OR_SUB(s, i, length, c, U_SENTINEL)

    /**
     * Append a code point to a string, overwriting 1 to 4 bytes.
     * The offset points to the current end of the string contents
     * and is advanced (post-increment).
     * "Unsafe" macro, assumes a valid code point and sufficient space in the string.
     * Otherwise, the result is undefined.
     *
     * @param s const uint8_t * string buffer
     * @param i string offset
     * @param c code point to append
     * @see U8_APPEND
     * @stable ICU 2.4
     */
    #define U8_APPEND_UNSAFE(s, i, c) UPRV_BLOCK_MACRO_BEGIN { \
        uint32_t __uc=(c); \
        if(__uc<=0x7f) { \
            (s)[(i)++]=(uint8_t)__uc; \
        } else { \
            if(__uc<=0x7ff) { \
                (s)[(i)++]=(uint8_t)((__uc>>6)|0xc0); \
            } else { \
                if(__uc<=0xffff) { \
                    (s)[(i)++]=(uint8_t)((__uc>>12)|0xe0); \
                } else { \
                    (s)[(i)++]=(uint8_t)((__uc>>18)|0xf0); \
                    (s)[(i)++]=(uint8_t)(((__uc>>12)&0x3f)|0x80); \
                } \
                (s)[(i)++]=(uint8_t)(((__uc>>6)&0x3f)|0x80); \
            } \
            (s)[(i)++]=(uint8_t)((__uc&0x3f)|0x80); \
        } \
    } UPRV_BLOCK_MACRO_END

    // common/unicode/utf16.h

    /**
     * Does this code unit alone encode a code point (BMP, not a surrogate)?
     * @param c 16-bit code unit
     * @return true or false
     * @stable ICU 2.4
     */
    #define U16_IS_SINGLE(c) !U_IS_SURROGATE(c)

    /**
     * Is this code unit a lead surrogate (U+d800..U+dbff)?
     * @param c 16-bit code unit
     * @return true or false
     * @stable ICU 2.4
     */
    #define U16_IS_LEAD(c) (((c)&0xfffffc00)==0xd800)

    /**
     * Is this code unit a trail surrogate (U+dc00..U+dfff)?
     * @param c 16-bit code unit
     * @return true or false
     * @stable ICU 2.4
     */
    #define U16_IS_TRAIL(c) (((c)&0xfffffc00)==0xdc00)

    /**
     * Is this code unit a surrogate (U+d800..U+dfff)?
     * @param c 16-bit code unit
     * @return true or false
     * @stable ICU 2.4
     */
    #define U16_IS_SURROGATE(c) U_IS_SURROGATE(c)

    /**
     * Helper constant for U16_GET_SUPPLEMENTARY.
     * @internal
     */
    #define U16_SURROGATE_OFFSET ((0xd800<<10UL)+0xdc00-0x10000)

    /**
     * Get a supplementary code point value (U+10000..U+10ffff)
     * from its lead and trail surrogates.
     * The result is undefined if the input values are not
     * lead and trail surrogates.
     *
     * @param lead lead surrogate (U+d800..U+dbff)
     * @param trail trail surrogate (U+dc00..U+dfff)
     * @return supplementary code point (U+10000..U+10ffff)
     * @stable ICU 2.4
     */
    #define U16_GET_SUPPLEMENTARY(lead, trail) \
        (((icu::UChar32)(lead)<<10UL)+(icu::UChar32)(trail)-U16_SURROGATE_OFFSET)

    /**
     * Append a code point to a string, overwriting 1 or 2 code units.
     * The offset points to the current end of the string contents
     * and is advanced (post-increment).
     * "Unsafe" macro, assumes a valid code point and sufficient space in the string.
     * Otherwise, the result is undefined.
     *
     * @param s const UChar * string buffer
     * @param i string offset
     * @param c code point to append
     * @see U16_APPEND
     * @stable ICU 2.4
     */
    #define U16_APPEND_UNSAFE(s, i, c) UPRV_BLOCK_MACRO_BEGIN { \
        if((uint32_t)(c)<=0xffff) { \
            (s)[(i)++]=(uint16_t)(c); \
        } else { \
            (s)[(i)++]=(uint16_t)(((c)>>10)+0xd7c0); \
            (s)[(i)++]=(uint16_t)(((c)&0x3ff)|0xdc00); \
        } \
    } UPRV_BLOCK_MACRO_END
}

#endif //CHARACTER_ICU_UTF_H
