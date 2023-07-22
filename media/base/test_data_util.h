//
// Created by wangrl2016 on 2023/7/22.
//

#ifndef CHARACTER_TEST_DATA_UTIL_H
#define CHARACTER_TEST_DATA_UTIL_H

#include "base/files/file_path.h"
#include "media/base/decoder_buffer.h"

namespace media {
    // Return a file path for a file in the res/media/test directory.
    base::FilePath GetTestDataFilePath(const std::string& name);

    // Return relative path for test data folder: res/media/test.
    base::FilePath GetTestDataPath();

    // Returns the mime type for res/media/test/<file_name>.
    std::string GetMiniTypeForFile(const std::string& file_name);

    std::shared_ptr<DecoderBuffer> ReadTestDataFile(const std::string& name);
}

#endif //CHARACTER_TEST_DATA_UTIL_H
