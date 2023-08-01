//
// Created by wangrl2016 on 2023/7/31.
//

#ifndef CHARACTER_FILE_UTIL_H
#define CHARACTER_FILE_UTIL_H

#include "base/files/file_path.h"

namespace base {
    // Return the file size. Returns true on success.
    bool GetFileSize(const FilePath& file_path, size_t* file_size);

    // Reads at most the given number of bytes from the file into the buffer.
    // Returns the number of read bytes, or -1 on error.
    size_t ReadFile(const FilePath& filename, char* data, int max_size);

    // Writes the given buffer into the file, overwriting any data that was
    // previously there. Returns the number of bytes written, or -1 on error.
    // If file doesn't exist, it gets create with read/write permissions for all.
    int WriteFile(const FilePath& filename, const char* data, int size);
}

#endif //CHARACTER_FILE_UTIL_H
