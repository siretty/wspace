cmake_minimum_required(VERSION 3.20)

project(wspace)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  enable_testing()
  add_subdirectory(third_party/googletest EXCLUDE_FROM_ALL)
endif ()

add_subdirectory(third_party)

include(cmake/wspace.cmake)

add_subdirectory(modules/support)
add_subdirectory(modules/gfx)
add_subdirectory(modules/runtime)

add_subdirectory(src/wspace-client)
