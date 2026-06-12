# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(program)

set(CMAKE_CXX_STANDARD 17)  # Set C++ version to C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Require the specified version
# set(CMAKE_CXX_EXTENSIONS OFF)  # Disable compiler-specific extensions

# Set the source directory
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

# Find all source files in the src directory and its subdirectories
file(GLOB_RECURSE SOURCES src/*.c src/*.cpp src/*.h src/*.hpp)

# Add executable target with all files from /src
add_executable(program ${SOURCES})

# Find and link SDL2 and SDL2_image
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

link_directories(/usr/lib/x86_64-linux-gnu)
target_link_libraries(program SDL2_image)

# Link against the necessary libraries
target_link_libraries(program ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

# Set compiler options (optional, but can help with warnings)
# target_compile_options(dvd-logo PRIVATE -Wall -Wextra -pedantic)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
