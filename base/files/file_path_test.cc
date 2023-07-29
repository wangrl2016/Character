//
// Created by wangrl2016 on 2023/7/28.
//

#include <gtest/gtest.h>
#include "base/config/build_config.h"
#include "base/files/file_path.h"

namespace base {
    // This macro helps avoid wrapped lines in the test structs.
    #define FPL(x) FILE_PATH_LITERAL(x)

    struct UnaryTestData {
        FilePath::StringPieceType input;
        FilePath::StringPieceType expected;
    };

    struct BinaryBooleanTestData {
        FilePath::StringPieceType inputs[2];
        bool expected;
    };

    typedef testing::Test FilePathTest;

    TEST_F(FilePathTest, PathComponentsTest) {
        const struct UnaryTestData cases[] = {
                {FPL("//foo/bar/baz"), FPL("|//|foo|bar|baz")},
                {FPL("///"), FPL("|/")},
#if defined(OS_POSIX)
                {FPL("///foo//bar/baz"), FPL("|/|foo|bar|baz")},
#else

#endif
        };

        for (size_t i = 0; i < std::size(cases); i++) {
            FilePath input(cases[i].input);
            std::vector<FilePath::StringType> comps = input.GetComponents();

            FilePath::StringType observed;
            for (const auto& j : comps) {
                observed.append(FILE_PATH_LITERAL("|"), 1);
                observed.append(j);
            }
            EXPECT_EQ(FilePath::StringType(cases[i].expected), observed) <<
                    "i: " << i << ", input " << input.value();
        }
    }

    TEST_F(FilePathTest, IsParentTest) {
        const struct BinaryBooleanTestData cases[] = {
                {{FPL("/"), FPL("/foo/bar/baz")}, true},
        };

        for (size_t i = 0; i < std::size(cases); i++) {
            FilePath parent(cases[i].inputs[0]);
            FilePath child(cases[i].inputs[1]);

            EXPECT_EQ(parent.IsParent(child), cases[i].expected) <<
                    "i: " << i << ", parent: " << parent.value() << ", child: " <<
                    child.value();
        }
    }

    TEST_F(FilePathTest, DirName) {
        const struct UnaryTestData cases[] = {
                {FPL(""), FPL(".")},
                {FPL("aa"), FPL(".")},
                {FPL("/aa/bb"), FPL("/aa")},
                {FPL("/aa/bb/"), FPL("/aa")},
                {FPL("/aa/bb//"), FPL("/aa")},
                {FPL("/aa/bb/ccc"), FPL("/aa/bb")},
                {FPL("/aa"), FPL("/")},
                {FPL("/"), FPL("/")},
                {FPL("//"), FPL("//")},
                {FPL("///"), FPL("/")},
                {FPL("aa/"), FPL(".")},
                {FPL("aa/bb"), FPL("aa")},
                {FPL("aa/bb/"), FPL("aa")},
                {FPL("aa/bb//"), FPL("aa")},
                {FPL("aa//bb//"), FPL("aa")},
                {FPL("aa//bb/"), FPL("aa")},
                {FPL("aa//bb"), FPL("aa")},
                {FPL("//aa/bb"), FPL("//aa")},
                {FPL("//aa/"), FPL("//")},
                {FPL("//aa"), FPL("//")},
#if defined(OS_POSIX)
                {FPL("///aa/"), FPL("/")},
                {FPL("///aa"), FPL("/")},
                {FPL("///"), FPL("/")},
#endif
                {FPL("0:"), FPL(".")},
                {FPL("@:"), FPL(".")},
                {FPL("[:"), FPL(".")},
                {FPL("`:"), FPL(".")},
                {FPL("{:"), FPL(".")},
                {FPL("\xB3:"), FPL(".")},
                {FPL("\xC5:"), FPL(".")},
                {FPL("/aa/../bb/cc"), FPL("/aa/../bb")},

        };

        for (size_t i = 0; i < std::size(cases); i++) {
            FilePath input(cases[i].input);
            FilePath observed = input.DirName();
            EXPECT_EQ(FilePath::StringType(cases[i].expected), observed.value()) <<
                    "i: " << i << ", input: " << input.value();
        }
    }

    TEST_F(FilePathTest, BaseName) {
        const struct UnaryTestData cases[] = {
                {FPL(""), FPL("")},
                {FPL("aa"), FPL("aa")},
                {FPL("/aa/bb"), FPL("bb")},
                {FPL("/aa/bb/"), FPL("bb")},
                {FPL("/aa/bb//"), FPL("bb")},
                {FPL("/aa/bb/ccc"), FPL("ccc")},
                {FPL("/aa"), FPL("aa")},
                {FPL("/"), FPL("/")},
                {FPL("//"), FPL("//")},
                {FPL("///"), FPL("/")},
        };

        for (size_t i = 0; i < std::size(cases); i++) {
            FilePath input(cases[i].input);
            FilePath observed = input.BaseName();
            EXPECT_EQ(FilePath::StringType(cases[i].expected), observed.value()) <<
                    "i: " << i << ", input: " << input.value();
        }
    }
}
