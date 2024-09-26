cmake_minimum_required(VERSION 3.16)
project(qassert-meta VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -Werror)

add_subdirectory(qassert-meta-lib)
