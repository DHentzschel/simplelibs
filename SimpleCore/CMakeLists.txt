cmake_minimum_required (VERSION 2.6)

project (SimpleCore)

add_compile_definitions(SIMPLECORE_EXPORTS)
set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "*.cpp")
add_library(SimpleCore SHARED ${SOURCES})
