set(BASE_LIBRARY_SOURCES
        base/config/build_config.h
        base/files/file_path.cc
        base/files/file_path.h
        base/files/file_util.cc
        base/files/file_util.h
        base/memory/aligned_memory.cc
        base/memory/aligned_memory.h
        base/string/string_concat.h
        base/string/string_piece.cc
        base/string/string_piece.h
        base/string/string_util.cc
        base/string/string_util.h
        base/string/string_util_impl_helper.h
        base/time/time_delta.cc
        base/time/time_delta.h

        PARENT_SCOPE
        )

set(BASE_LIBRARY_TEST_SOURCES
        base/files/file_path_test.cc
        base/string/string_concat_test.cc
        PARENT_SCOPE
        )
