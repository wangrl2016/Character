//
// Created by wangrl2016 on 2023/6/3.
//

#ifndef CHARACTER_ALIGNED_MEMORY_H
#define CHARACTER_ALIGNED_MEMORY_H

#if defined(COMPILER_MSVC)
#include <malloc.h>
#else

#include <cstdlib>

#endif

#include "base/config/build_config.h"

namespace base {
    void* AlignedAlloc(size_t size, size_t alignment);

    inline void AlignedFree(void* ptr) {
#if defined(COMPILER_MSVC)
        _aligned_free(ptr);
#else
        free(ptr);
#endif
    }

    // Deleter for use with unique_ptr. E.g., use as
    // std::unique_ptr<Foo, base::AlignedFreeDeleter> foo;
    struct AlignedFreeDeleter {
        inline void operator()(void* ptr) const {
            AlignedFree(ptr);
        }
    };

    inline bool IsAligned(uintptr_t val, size_t alignment) {
        return (val & (alignment - 1)) == 0;
    }

    inline bool IsAligned(const void* val, size_t alignment) {
        return IsAligned(reinterpret_cast<uintptr_t>(val), alignment);
    }
}

#endif //CHARACTER_ALIGNED_MEMORY_H
