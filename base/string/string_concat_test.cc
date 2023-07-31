//
// Created by wangrl2016 on 2023/7/30.
//

#include <gtest/gtest.h>
#include "base/string/string_concat.h"

namespace base {
    TEST(StringConcat, 8Bit) {
        EXPECT_EQ("", StringConcat({""}));
        EXPECT_EQ("1", StringConcat({"1"}));
        EXPECT_EQ("122", StringConcat({"1", "22"}));
        EXPECT_EQ("122333", StringConcat({"1", "22", "333"}));
        EXPECT_EQ("1223334444", StringConcat({"1", "22", "333", "4444"}));
    }

    TEST(StringConcat, 16Bit) {
        std::u16string arg1 = u"1";
        std::u16string arg2 = u"22";
        std::u16string arg3 = u"333";

        EXPECT_EQ(u"", StringConcat({std::u16string()}));
        EXPECT_EQ(u"1", StringConcat({arg1}));
        EXPECT_EQ(u"122", StringConcat({arg1, arg2}));
        EXPECT_EQ(u"122333", StringConcat({arg1, arg2, arg3}));
    }

    TEST(StringAppend, 8Bit) {
        std::string result;

        result = "foo";
        StringAppend(&result, {std::string()});
        EXPECT_EQ("foo", result);

        result = "foo";
        StringAppend(&result, {"1"});
        EXPECT_EQ("foo1", result);

        result = "foo";
        StringAppend(&result, {"1", "22", "333"});
        EXPECT_EQ("foo122333", result);
    }

    TEST(StringAppend, 16Bit) {
        std::u16string arg1 = u"1";
        std::u16string arg2 = u"22";
        std::u16string arg3 = u"333";

        std::u16string result;

        result = u"foo";
        StringAppend(&result, {std::u16string()});
        EXPECT_EQ(u"foo", result);

        result = u"foo";
        StringAppend(&result, {arg1});
        EXPECT_EQ(u"foo1", result);

        result = u"foo";
        StringAppend(&result, {arg1, arg2, arg3});
        EXPECT_EQ(u"foo122333", result);
    }
}
