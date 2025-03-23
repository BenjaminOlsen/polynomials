cmake_minimum_required(VERSION 3.14)
project(libpolyTest)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "---> Using GCC compiler")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "---> Using Clang compiler")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "---> Using MSVC compiler")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    message(STATUS "---> Using Intel compiler")
else()
    message(STATUS "---> Using an unknown compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

include(FetchContent)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
message(STATUS "PARENT_DIR: ${PARENT_DIR}")
message(STATUS "BINARY_DIR: ${CMAKE_BINARY_DIR}")

#set(LIBPOLY_SOURCES
#    ${CMAKE_SOURCE_DIR}/poly.cpp
#)
#
#set(LIBPOLY_HEADERS
#    ${PARENT_DIR}/telemetry/poly.hpp
#)

# Add the main project executable
#add_library(libpoly ${LIBPOLY_SOURCES})# ${LIBPOLY_HEADERS})

# Specify language for the library
#set_target_properties(libpoly PROPERTIES LINKER_LANGUAGE CXX)

# Add the test executable
add_executable(test_poly test_poly.cpp)

# Include directories for headers
#target_include_directories(libpoly PUBLIC ${PARENT_DIR})

#if(MSVC)
#  target_compile_options(test_poly PRIVATE /W4 /WX)
#else()
#  target_compile_options(test_poly PRIVATE -Wall -Wextra -Wpedantic -Werror)
#endif()
#
# For extra verbose debug info:
#target_compile_definitions(libpoly PRIVATE _PRINT_DEBUG_INFO)
#target_compile_definitions(test_poly PRIVATE _PRINT_DEBUG_INFO)

# GoogleTest :
target_link_libraries(test_poly GTest::gtest_main)

include(GoogleTest)

gtest_discover_tests(test_poly)
