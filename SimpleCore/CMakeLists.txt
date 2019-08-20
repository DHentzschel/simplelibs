cmake_minimum_required(VERSION 3.13.4 FATAL_ERROR)

project(simplecore)

add_compile_options("-std=c++17")

# Source files
file(GLOB SOURCES *.cpp)

# Header files
include_directories(.)

# Create shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# Install library headers
file(GLOB HEADERS *.h)
install(FILES ${HEADERS} DESTINATION ${PROJECT_NAME})
