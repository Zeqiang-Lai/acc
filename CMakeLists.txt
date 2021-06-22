# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.1)

# Set the project name
project (acc)

# set the C++ standard to C++ 20
set(CMAKE_CXX_STANDARD 20)

# Add an executable
aux_source_directory(src ALL_SRCS)
add_executable(acc ${ALL_SRCS})
