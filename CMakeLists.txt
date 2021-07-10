# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.1)

# Set the project name
project (acc)

# set the C++ standard to C++ 20
set(CMAKE_CXX_STANDARD 20)

# add LLVM
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader)

# Add an executable
aux_source_directory(src ALL_SRCS)
add_executable(acc ${ALL_SRCS} src/span.cpp src/span.h)

# Link against LLVM libraries
target_link_libraries(acc ${llvm_libs})