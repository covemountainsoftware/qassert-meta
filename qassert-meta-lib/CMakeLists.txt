include_directories(include)

add_library(qassert-meta-lib
        src/qassert-meta.c)


add_subdirectory(tests)


target_include_directories(qassert-meta-lib PUBLIC
        include)
