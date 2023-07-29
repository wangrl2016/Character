//
// Created by wangrl2016 on 2023/7/22.
//

#include "config/user_config.h"
#include "media/base/test_data_util.h"

namespace media {
    const base::FilePath::CharType kTestDataPath[] =
            FILE_PATH_LITERAL("res/media/test");

    base::FilePath GetTestDataFilePath(const std::string& name) {
        base::FilePath file_path(FILE_PATH_LITERAL(PROJECT_SOURCE_DIR));
        return file_path.Append(GetTestDataPath()).AppendASCII(name);
    }
}