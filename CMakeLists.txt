cmake_minimum_required(VERSION 2.6)
project(atomic)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wfatal-errors")

file(GLOB_RECURSE atomic_sources ./src/*.cpp)

add_library(atomic ${atomic_sources})

file(COPY "src/" DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/atomic/ FILES_MATCHING PATTERN "*.hpp" PATTERN "*.inl")
file(COPY "LICENSE" DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/atomic/)