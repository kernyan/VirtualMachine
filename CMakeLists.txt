project(VirtualMachine)
cmake_minimum_required(VERSION 2.8.7)
add_definitions(-std=c++14 -pipe -lm)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
file(GLOB SRCS ${PROJECT_SOURCE_DIR}/*.cpp)
add_library(lib STATIC ${SRCS})
add_subdirectory(test)

set(Main_SRC virtualmachine.cpp)
include_directories(${PROJECT_SOURCE_DIR})
add_executable(VirtualMachine ${Main_SRC})
target_link_libraries(VirtualMachine lib)

