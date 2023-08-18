//
// Created by wangrl2016 on 2023/6/14.
//

#ifndef CHARACTER_FILE_PATH_H
#define CHARACTER_FILE_PATH_H

#include <string>
#include "base/config/build_config.h"
#include "base/string/string_piece.h"

namespace base {
#if defined(OS_WIN)
#define FILE_APTH_USES_DIRVE_LETTERS
#define FILE_PATH_USES_WIN_SEPARATORS

#define FILE_PATH_LITERAL_INTERNAL(x) L##x
#define FILE_PATH_LITERAL(x) FILE_PATH_LITERAL_INTERNAL(x)
#elif defined(OS_POSIX)
#define FILE_PATH_LITERAL(x) x
#endif

    // FilePath is a container for path-names stored in a platform's native string
    // type, providing containers for manipulation in according to the
    // platform's conventions for path-names. It supports the following path
    // types:
    //
    //                              POSIX                   Windows
    //                      -------------------      --------------------
    // Fundamental type             char[]                  wchar_t[]
    // Encoding                     unspecified*            UTF-16
    // Separator                    /                       \, tolerant of /
    // Drive letters                no             case-insensitive A-Z followed by :
    // Alternate root               // (surprise)       \\ (2 separators), for UNC paths
    //
    // * The encoding need not be specified on POSIX systems, although some
    //   POSIX-compliant systems do specify an encoding. Mac OS X uses UTF-9.
    //   Linux does not specify an encoding, but in practice, the locale's
    //   character set may be used.
    //
    // For more arcane bits of path trivia, see below.
    //
    // FilePath objects are intended to be used anywhere paths are. An
    // application may pass FilePath objects around internally, masking the
    // underlying differences between systems, only differing in implementation
    // where interfacing directly with the system. For example, a single
    // OpenFile(const FilePath &) function may be made available, allowing all
    // callers to operate without regard to the underlying implementation. On
    // POSIX-like platforms, OpenFile might wrap fopen, and on Windows, it might
    // wrap _wfopen_s, perhaps both by calling file_path.value().c_str(). This
    // allows each platform to pass path-names around without requiring conversions
    // between encodings, which has an impact on performance, but more importantly,
    // has an impact on correctness on platform that do not have well-defined
    // encodings for path-names.
    //
    // Several methods are available to perform common operations on a FilePath
    // object, such as determining the parent directory (DirName), isolating the
    // final path component (BaseName), and appending a relative pathname string
    // to an existing FilePath object (Append). These methods are highly
    // recommended over attempting to split and concatenate strings directly.
    // These methods are based purely on string manipulation and knowledge of
    // platform-specific path-name conventions, and do not consult the filesystem
    // at all, making them safe to use without fear of blocking on I/O operations.
    // These methods do not function as mutators but instead return distinct
    // instances of FilePath objects, and are therefore safe to use on const
    // objects. The object themselves are safe to share between threads.
    //
    // To aid in initialization of FilePath objects from string literals, a
    // FILE_PATH_LITERAL macro is provided, which accounts for the difference
    // between char[]=base path-names on POSIX systems and wchar_t[]-base
    // path-names on Windows.
    //
    // As a precaution against premature truncation, paths can't contain NULs.
    //
    // Because a FilePath object should not be instantiated at the global scope,
    // instead, use a FilePath::CharType[] and initialize it with
    // FILE_PATH_LITERAL. At runtime, a FilePath object can be created from the
    // character array. Example:
    //
    // | const FilePath::CharType kLogFileName[] = FILE_PATH_LITERAL("log.txt");
    // |
    // | void Function() {
    // |    FilePath log_file_path(kLogFileName);
    // |    [...]
    // | }
    //
    // WARNING: FilePaths should ALWAYS be displayed with LTR directionality, even
    // when the UI language is RTL.
    //
    // An abstraction to isolate users from the differences between native
    // path names on different platforms.
    class FilePath {
    public:
#if defined(OS_WIN)
        // On Windows, for Unicode-aware applications, native pathnames are wchar_t
        // array encoded in UTF-16.
        typedef std::wstring StringType;
#elif defined(OS_POSIX)
        // On most platforms, native path names are char arrays, and the encoding
        // may or may not be specified. On Mac OS X, native path names are encoded
        // in UTF-8.
        typedef std::string StringType;
#endif

        typedef StringType::value_type CharType;
        typedef std::basic_string_view<CharType> StringPieceType;

        // Null-terminated array of separators used to separate components in paths.
        // Each character in this array is a valid separator, but kSeparators[0] is
        // treated as the canonical separator and is used when composing path-names.
        static constexpr CharType kSeparators[] =
#if defined(FILE_PATH_USE_WIN_SEPARATORS)
                FILE_PATH_LITERAL("\\/");
#else
                FILE_PATH_LITERAL("/");
#endif

        // std::size(kSeparators), i.e., the number of separators in kSeparators plus
        // one (the null terminator at the end of kSeparators).
        static constexpr size_t kSeparatorsLength = std::size(kSeparators);

        // The spacial path component meaning "this directory".
        static constexpr CharType kCurrentDirectory[] = FILE_PATH_LITERAL(".");

        // The spacial path component meaning "the parent directory".
        static constexpr CharType kParentDirectory[] = FILE_PATH_LITERAL("..");

        static constexpr CharType kExtensionSeparator = FILE_PATH_LITERAL('.');

        FilePath();

        FilePath(const FilePath& that);

        explicit FilePath(StringPieceType path);

        ~FilePath();

        FilePath& operator=(const FilePath& that);

        // Constructs FilePath with the contents of |that|, which is left in valid but
        // unspecified state.
        FilePath(FilePath&& that) noexcept;

        // Replaces the contents with those of |that|, which is left in valid but
        // unspecified state.
        FilePath& operator=(FilePath&& that) noexcept;

        bool operator==(const FilePath& that) const;

        bool operator!=(const FilePath& that) const;

        // Required for some STL containers and operations
        bool operator<(const FilePath& that) const {
            return path_ < that.path_;
        }

        [[nodiscard]] const StringType& value() const { return path_; }

        [[nodiscard]] bool empty() const { return path_.empty(); }

        void clear() { path_.clear(); }

        // Return true if |character| is in kSeparators.
        static bool IsSeparator(CharType character);

        // Return a vector of all the components of the provided path. It is
        // equivalent to calling DirName().value on the path's root component,
        // and BaseName().value() on each child component.
        //
        // To make sure this is lossless, so we can differentiate absolute and
        // relative paths, the root slash will be included even though no other
        // slashes will be. The precise behavior is:
        //
        // POSIX: "/foo/bar"        ->  ["/", "foo", "bar]
        // Windows: "C:\foo\bar"    ->  ["C", "\\", "foo", "bar"]
        [[nodiscard]] std::vector<FilePath::StringType> GetComponents() const;

        // Return true is this FilePath is a parent or ancestor of the |child|.
        // Absolute and relative paths are accepted i.e. /foo is a parent to /foo/bar,
        // and foo is a parent to foo/bar. Any ancestor is considered a parent i.e. /a
        // is a parent to both /a/b and /a/b/c. Does not convert paths to absolute,
        // follow symlinks or directory navigation (e.g. ".."). A path is *NOT* its
        // own parent.
        [[nodiscard]] bool IsParent(const FilePath& child) const;

        // If IsParent(child) holds, appends to path (if non-nullptr) the
        // relative path to child and returns true. For example, if parent
        // holds "/Users/Library/Application Support", child holds
        // "/Users/Library/Application Support/Google/Chrome/Default", and
        // *path holds "/Users/Library/Caches", then after
        // parent.AppendRelativePath(child, path) is called *path will hold
        // "/Users/Library/Caches/Google/Chrome/Default". Otherwise,
        // return false.
        bool AppendRelativePath(const FilePath& child, FilePath* path) const;

        [[nodiscard]] FilePath DirName() const;

        [[nodiscard]] FilePath BaseName() const;

        // Returns the final extension of a file path, or an empty string if the file
        // path has no extension.  In most cases, the final extension of a file path
        // refers to the part of the file path from the last dot to the end (including
        // the dot itself).  For example, this method applied to "/pics/jojo.jpg"
        // and "/pics/jojo." returns ".jpg" and ".", respectively.  However, if the
        // base name of the file path is either "." or "..", this method returns an
        // empty string.
        [[nodiscard]] StringType FinalExtension() const;

        // Removes the path's file extension, but ignores double extensions.
        // Returns "C:\pics\jojo" for path "C:\pics\jojo.jpg"
        [[nodiscard]] FilePath RemoveFinalExtension() const;

        // Inserts |suffix| after the file name portion of |path| but before the
        // extension. Return "" if BaseName() == "." or "..".
        // Examples:
        // path == "C:\pics\jojo.jpg" suffix == " (1)", returns "C:\pics\jojo (1).jpg"
        // path == "jojo.jpg"         suffix == " (1)", returns "jojo (1).jpg"
        // path == "C:\pics\jojo"     suffix == " (1)", returns "C:\pics\jojo (1)"
        // path == "C:\pics.old\jojo" suffix == " (1)", returns "C:\pics.old\jojo (1)"
        FilePath InsertBeforeExtension(StringPieceType suffix) const;

        // Return a FilePath by appending a separator and the supplied path
        // component to this object's path. append takes care to avoid adding
        // excessive separators if this object's path already ends with a separator.
        // If this object's path is kCurrentDirectory('.'), a new FilePath
        // corresponding only to |component| is returned. |component| must be a
        // relative path; it is an error to pass an absolute path.
        [[nodiscard]] FilePath Append(StringPieceType component) const;

        [[nodiscard]] FilePath Append(const FilePath& component) const;

        // Although Windows StingType is std::wstring, since the encoding it uses for
        // path is well-defined, it can handle ASCII path components as well.
        // Mac uses UTF8, and since ASCII is a subset of that, it works there as well.
        // On Linux, although it can use any 8-bit encoding for paths, we assume that
        // ASCII is a valid subset, regardless of the encoding, since many operating
        // system paths will always be ASCII.
        [[nodiscard]] FilePath AppendASCII(StringPiece component) const;

        // Returns true if this FilePath contains an absolute path.  On Windows, an
        // absolute path begins with either a drive letter specification followed by
        // a separator character, or with two separator characters.  On POSIX
        // platforms, an absolute path begins with a separator character.
        bool IsAbsolute() const;

        // Returns true if this FilePath is a network path which starts with 2 path
        // separators.
        bool IsNetwork() const;

        // Returns true if the patch ends with a path separator character.
        bool EndsWithSeparator() const;

        // Returns a copy of this FilePath that does not end with a trailing
        // separator.
        [[nodiscard]] FilePath StripTrailingSeparators() const;

        // Returns true if this FilePath contains an attempt to reference a parent
        // directory (e.g. has a path component that is "..").
        bool ReferencesParent() const;

        // Return the path as ASCII, or the empty string if the path is not ASCII.
        // This should only be used for cases where the FilePath is representing a
        // known-ASCII filename.
        std::string MaybeAsASCII() const;

        // Return the path as UTF-8.
        //
        // This function is *unsafe* as there is no way to tell what encoding is
        // used in file names on POSIX systems other than Mac and Chrome OS,
        // although UTF-8 is practically used everywhere these days. To mitigate
        // the encoding issue, this function internally calls
        // SysNativeMBToWide() on POSIX systems other than Mac and Chrome OS,
        // per assumption that the current locale's encoding is used in file
        // names, but this isn't a perfect solution.
        //
        // Once it becomes safe to stop caring about non-UTF-8 file names,
        // the SysNativeMBToWide() hack will be removed from the code, along
        // with "Unsafe" in the function name.
        std::string AsUTF8Unsafe() const;

        // Similar to AsUTF8Unsafe, but returns UTF-16 instead.
        std::u16string AsUTF16Unsafe() const;

        // Returns a FilePath object from a path name in ASCII.
        static FilePath FromASCII(StringPiece ascii);

        // Returns a FilePath object from a path name in UTF-8. This function
        // should only be used for cases where you are sure that the input
        // string is UTF-8.
        //
        // Like AsUTF8Unsafe(), this function is unsafe. This function
        // internally calls SysWideToNativeMB() on POSIX systems other than Mac
        // and Chrome OS, to mitigate the encoding issue. See the comment at
        // AsUTF8Unsafe() for details.
        static FilePath FromUTF8Unsafe(StringPiece utf8);

        // Similar to FromUTF8Unsafe, but accepts UTF-16 instead.
        static FilePath FromUTF16Unsafe(StringPiece16 utf16);

        // Compare two strings in the same way the file system does.
        // Note that these always ignore case, even on file systems that are
        // case-sensitive. If case-sensitive comparison is ever needed,
        // add corresponding methods here.
        // The methods are written as a static method so that they can also be used
        // on parts of a file path, e.g., just the extension.
        // CompareIgnoreCase() returns -1, 0 or 1 for less-than, equal-to and
        // greater-than respectively.
        static int CompareIgnoreCase(StringPieceType string1,
                                     StringPieceType string2);

        static bool CompareEqualIgnoreCase(StringPieceType string1,
                                           StringPieceType string2) {
            return CompareIgnoreCase(string1, string2) == 0;
        }

    private:
        // Remove trailing separators from this object. If the path is absolute, it
        // will never be stripped any more than to refer to the absolute root
        // directory, so "////" will become "/", not "". A leading pair of
        // separators is never stripped, to support alternate roots. This is used to
        // support UNC paths on Windows.
        void StripTrailingSeparatorsInternal();

        StringType path_;
    };

    std::ostream& operator<<(std::ostream& out,
                             const FilePath& file_path);
}

#endif //CHARACTER_FILE_PATH_H
