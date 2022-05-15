cmake_minimum_required(VERSION 3.20)

project(wspace)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  enable_testing()
endif ()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(wspace)

add_subdirectory(libs)
add_subdirectory(src)
