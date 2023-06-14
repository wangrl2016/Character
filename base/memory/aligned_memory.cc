//
// Created by wangrl2016 on 2023/6/3.
//

// #include <glog/logging.h>
#include "base/memory/aligned_memory.h"

namespace base {
    void* AlignedAlloc(size_t size, size_t alignment) {
        // DCHECK_GT(size, 0U);
        // DCHECK_EQ(alignment % sizeof(void*), 0U);
        void* ptr = nullptr;
#if defined(COMPILER_MSVC)
        ptr = _aligned_malloc(size, alignment);
#else
        int ret = posix_memalign(&ptr, alignment, size);
        if (ret != 0) {
            // DLOG(ERROR) << "posix_memalign() returned with error " << ret;
            ptr = nullptr;
        }
#endif

        // Since aligned allocations may fail for non-memory related reasons, force
        // a crash if we encounter a failed allocation.
        if (!ptr) {
            // DLOG(ERROR) << "If you crashed here, your aligned allocation is incorrect: "
            //         << "size = " << size << ", alignment = " << alignment;
            // CHECK(false);
        }

        // Sanity check alignment just to be safe.
        // DCHECK(base::IsAligned(ptr, alignment));
        return ptr;
    }
}
