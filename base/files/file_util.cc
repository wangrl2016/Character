//
// Created by wangrl2016 on 2023/7/31.
//

#include <filesystem>
#include <fstream>
#include "base/files/file_util.h"

namespace base {
    bool GetFileSize(const FilePath& file_path, size_t* file_size) {
        *file_size = std::filesystem::file_size(file_path.value().c_str());
        return *file_size > 0;
    }

    size_t ReadFile(const FilePath& filename, char* data, int max_size) {
        if (max_size < 0)
            return -1;
        std::fstream fs{filename.value().c_str(), std::ios::in};
        if (!fs.is_open()) {
            return -1;
        } else {
            fs.read(data, max_size);
        }
        return fs.gcount();
    }
}
