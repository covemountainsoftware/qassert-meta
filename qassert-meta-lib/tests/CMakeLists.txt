if(DEFINED ENV{CPPUTEST_HOME})
    message(STATUS "Using CppUTest home: $ENV{CPPUTEST_HOME}")
    set(CPPUTEST_INCLUDE_DIRS $ENV{CPPUTEST_HOME}/include)
    set(CPPUTEST_LIBRARIES $ENV{CPPUTEST_HOME}/lib)
    set(CPPUTEST_LDFLAGS CppUTest CppUTestExt)
else()
    find_package(PkgConfig REQUIRED)
    pkg_search_module(CPPUTEST REQUIRED cpputest>=3.8)
    message(STATUS "Found CppUTest version ${CPPUTEST_VERSION}")
endif()

if (CMS_ENABLE_QASSERT_META_QPC)
    add_definitions(-DTESTS_FOR_QPC)
elseif (CMS_ENABLE_QASSERT_META_QPCPP)
    add_definitions(-DTESTS_FOR_QPCPP)
else ()
    message(FATAL_ERROR "Neither QPC nor QPCPP defined, fatal at this point.")
endif ()

set(TEST_APP_NAME qassert-meta-lib-tests)
set(TEST_SOURCES
        main.cpp
        qassert-meta-lib-tests.cpp
)

include_directories(${CPPUTEST_INCLUDE_DIRS})
link_directories(${CPPUTEST_LIBRARIES})

add_executable(${TEST_APP_NAME} ${TEST_SOURCES})
target_link_libraries(${TEST_APP_NAME} ${APP_LIB_NAME} ${CPPUTEST_LDFLAGS} qassert-meta-lib)

# (5) Run the test once the build is done
add_custom_command(TARGET ${TEST_APP_NAME} COMMAND ./${TEST_APP_NAME} POST_BUILD)