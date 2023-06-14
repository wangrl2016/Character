//
// Created by wangrl2016 on 2023/6/14.
//

#ifndef CHARACTER_FILE_PATH_H
#define CHARACTER_FILE_PATH_H

#include <string>

namespace base {

    // An abstraction to isolate users from the differences between native
    // path names on different platforms.
    class FilePath {
    public:
#if defined(OS_WIN)
        // On Windows, for Unicode-aware applications, native pathnames are wchar_t
        // array encoded in UTF-16.
        typedef std::wstring StringType;
#else
        // On most platforms, native path names are char arrays, and the encoding
        // may or may not be specified. On Mac OS X, native path names are encoded
        // in UTF-8.
        typedef std::string StringType;
#endif
    };
}

#endif //CHARACTER_FILE_PATH_H
