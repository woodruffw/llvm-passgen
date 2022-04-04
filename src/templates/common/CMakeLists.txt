cmake_minimum_required(VERSION 3.4.3 FATAL_ERROR)

find_package(LLVM REQUIRED CONFIG HINTS)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

set(CMAKE_MODULE_PATH $ENV{LLVM_DIR})
set(CMAKE_CXX_STANDARD 17)

include(LLVMConfig)
include(HandleLLVMOptions)
include(AddLLVM)

add_llvm_library(LLVM{{ pass_name }} MODULE BUILDTREE_ONLY {{ pass_name }}.cpp)
