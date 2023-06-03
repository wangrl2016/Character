//
// Created by wangrl2016 on 2023/6/3.
//

#ifndef CHARACTER_BUILD_CONFIG_H
#define CHARACTER_BUILD_CONFIG_H

#if defined(ANDROID)
#define OS_ANDROID 1
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#define OS_IOS 1
#else
#define OS_MAC 1
#endif
#elif defined(__linux__)
#define OS_LINUX 1
#elif defined(_WIN32)
#define OS_WIN
#else
#error Please add support for your platform in build_config.h
#endif

// Compiler detection. Note: clang masquerades as GCC on POSIX and
// as MSVC on Windows.
#if defined(__GNUC__)
#define COMPILER_GCC 1
#elif defined(_MSC_VER)
#define COMPILER_MSVC 1
#else
#error Please add support for your compiler in build_config.h
#endif

#endif //CHARACTER_BUILD_CONFIG_H
