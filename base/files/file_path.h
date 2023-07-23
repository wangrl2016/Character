//
// Created by wangrl2016 on 2023/6/14.
//

#ifndef CHARACTER_FILE_PATH_H
#define CHARACTER_FILE_PATH_H

#include <string>
#include "base/config/build_config.h"

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

        bool empty() const { return path_.empty(); }

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

        FilePath DirName() const;

        FilePath BaseName() const;

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
