//
// Created by wangrl2016 on 2023/7/22.
//

#include "config/user_config.h"
#include "media/base/test_data_util.h"
#include "base/files/file_util.h"

namespace media {
    const base::FilePath::CharType kTestDataPath[] =
            FILE_PATH_LITERAL("res/media/test");

    base::FilePath GetTestDataFilePath(const std::string& name) {
        base::FilePath file_path(FILE_PATH_LITERAL(PROJECT_SOURCE_DIR));
        return file_path.Append(GetTestDataPath()).AppendASCII(name);
    }

    base::FilePath GetTestDataPath() {
        return base::FilePath(kTestDataPath);
    }

    std::shared_ptr<DecoderBuffer> ReadTestDataFile(const std::string& name) {
        base::FilePath file_path = GetTestDataFilePath(name);

        size_t file_size = 0;
        CHECK(base::GetFileSize(file_path, &file_size))
                        << "Failed to get file size for " << name;

        std::shared_ptr<DecoderBuffer> buffer(new DecoderBuffer(file_size));
        auto* data = reinterpret_cast<char*>(buffer->data());
        CHECK_EQ(file_size, base::ReadFile(file_path, data, file_size))
            << "Failed to read " << name;

        return buffer;
    }
}
