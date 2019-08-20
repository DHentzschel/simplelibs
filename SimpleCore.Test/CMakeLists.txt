cmake_minimum_required(VERSION 3.13.4 FATAL_ERROR)

project(simplecore-test)

add_compile_options("-std=c++17")

add_definitions(-DSIMPLELIBS_TEST)

# Source files
file(GLOB SOURCES *.cpp)

# Header files
include_directories(.)

# Include library headers
include_directories(../SimpleCore/.)
include_directories(../../SimpleCore/.)

# Link directory of shared library
link_directories(${CMAKE_CURRENT_BINARY_DIR})

# Specify library file name
find_library(SIMPLECORE_LIB simplecore)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link library
target_link_libraries(${PROJECT_NAME} simplecore)
