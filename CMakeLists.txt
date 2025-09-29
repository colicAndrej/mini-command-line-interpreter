cmake_minimum_required(VERSION 3.20)
project(mini-command-line-interpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
     src/*.cpp)

add_library(cli_core ${SRC_FILES})
target_include_directories(cli_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(cli apps/cli.cpp)
target_link_libraries(cli PRIVATE cli_core)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES} apps/cli.cpp)