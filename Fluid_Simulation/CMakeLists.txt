cmake_minimum_required(VERSION 3.26)
project( fluid LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set compiler options
add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} −march=native")

#set(CMAKE_CXX_CLANG_TIDY clang−tidy −header−filter=.∗)

# All includes relative to source tree root.
include_directories (PUBLIC .)
# Process cmake from sim and fluid directories
add_subdirectory(sim)
add_subdirectory(fluid)
# Uncomment these if you have tests set up and they have their own CMakeLists.txt
# add_subdirectory(utest)
# add_subdirectory(ftest)
