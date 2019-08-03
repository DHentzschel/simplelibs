cmake_minimum_required (VERSION 2.6)

project (SimpleCore)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "*.cpp")
add_library(SimpleCore SHARED ${SOURCES})
