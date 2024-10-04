include_directories(include)

add_library(qassert-meta-lib  src/qassert-meta.c)

if (CMS_ENABLE_QASSERT_META_QPC)
elseif (CMS_ENABLE_QASSERT_META_QPCPP)
else ()
    message(STATUS "Neither QP/C nor QP/C++ defined, will build qassert-meta-lib for QP/C by default.")
    option(CMS_ENABLE_QASSERT_META_QPC "Internal QAssert Meta Data is for QP/C" ON)
endif ()

if (CMS_ENABLE_QASSERT_META_QPC)
    target_sources(qassert-meta-lib PRIVATE src/qassert-meta-qpc-data.c)
elseif (CMS_ENABLE_QASSERT_META_QPCPP)
    target_sources(qassert-meta-lib PRIVATE src/qassert-meta-qpcpp-data.c)
else ()
    message(FATAL_ERROR "Neither QPC nor QPCPP defined, fatal at this point.")
endif ()

add_subdirectory(tests)

target_include_directories(qassert-meta-lib PUBLIC
        include)
