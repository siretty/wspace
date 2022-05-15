
function(wspace_internal_library target_name)
  set(_option_args "")
  set(_one_value_args "")
  set(
      _multi_value_args
      COMPONENT
      SOURCE HEADER
      UTEST_SOURCE UTEST_HEADER
      LINK_PUBLIC
  )
  cmake_parse_arguments(
      ARG "${_option_args}" "${_one_value_args}" "${_multi_value_args}"
      ${ARGN}
  )

  set(_sources "${ARG_SOURCE}")
  set(_headers "${ARG_HEADER}")
  set(_utest_sources "${ARG_UTEST_SOURCE}")
  set(_utest_headers "${ARG_UTEST_HEADER}")

  foreach (_component IN LISTS ARG_COMPONENT)
    file(REAL_PATH "${_component}.cpp" _component_source)

    if (EXISTS "${_component_source}")
      list(APPEND _sources "${_component_source}")
    else ()
      message(WARNING "wspace: component '${_component}' source file '${_component_source}' does not exist")
    endif ()

    file(REAL_PATH "${_component}.hpp" _component_header)
    if (EXISTS "${_component_source}")
      list(APPEND _headers "${_component_header}")
    else ()
      message(WARNING "wspace: component '${_component}' header file '${_component_header}' does not exist")
    endif ()

    file(REAL_PATH "${_component}.utest.cpp" _component_utest_source)
    if (EXISTS "${_component_utest_source}")
      list(APPEND _utest_sources "${_component_utest_source}")
    else ()
      message(DEBUG "wspace: component '${_component}' unit test source file '${_component_utest_source}' does not exist")
    endif ()

    file(REAL_PATH "${_component}.utest.hpp" _component_utest_header)
  endforeach ()

  add_library(
      "${target_name}_objects" OBJECT
      ${_sources}
      ${_headers}
  )
  target_link_libraries(
      "${target_name}_objects"
      PRIVATE ${ARG_LINK_PUBLIC}
  )
  set_target_properties(
      "${target_name}_objects" PROPERTIES
      CXX_STANDARD 20
  )

  add_library(
      "${target_name}" STATIC
      $<TARGET_OBJECTS:${target_name}_objects>
  )
  target_include_directories(
      "${target_name}"
      INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}"
  )
  target_link_libraries(
      "${target_name}"
      PUBLIC ${ARG_LINK_PUBLIC}
  )
  set_target_properties(
      "${target_name}" PROPERTIES
      CXX_STANDARD 20
  )

  list(LENGTH _utest_sources _utest_sources_count)
  if (_utest_sources_count GREATER 0)
    include(wspace_googletest)

    add_executable(
        "${target_name}_utest"
        ${_utest_sources}
        ${_utest_headers}
        $<TARGET_OBJECTS:${target_name}_objects>
    )
    target_link_libraries(
        "${target_name}_utest"
        ${ARG_LINK_PUBLIC}
        gtest_main
    )
    set_target_properties(
        "${target_name}_utest" PROPERTIES
        CXX_STANDARD 20
    )

    message(STATUS "wspace: unit tests: ${target_name}")
    add_test(NAME "${target_name}_unit_tests" COMMAND $<TARGET_FILE:${target_name}_utest>)
  endif ()
endfunction()
