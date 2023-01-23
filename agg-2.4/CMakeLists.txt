cmake_minimum_required(VERSION 3.21.0)

project(agg)

set(AGG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" PARENT_SCOPE)
FILE(GLOB AGG_HEADERS "${AGG_INCLUDE_DIR}/*.h")
FILE(GLOB AGG_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(agg ${AGG_HEADERS} ${AGG_SOURCES})
target_include_directories(agg PRIVATE "${AGG_INCLUDE_DIR}")
