
include("${CMAKE_CURRENT_LIST_DIR}/wspace_parse_arguments.cmake")

function(wspace_module module_name)
  wspace_parse_arguments(
      ARG "${ARGN}"
      _OVALUE SOURCE_DIRECTORY
      _OVALUE COMPONENT_BASE
      _MVALUE COMPONENT
      _MVALUE LINK_PUBLIC
      _MVALUE LINK_MODULE
  )

  set(_module_source_files "")
  set(_module_header_files "")

  set(_module_utest_executable_targets "")

  foreach (_component IN LISTS ARG_COMPONENT)
    list(APPEND _module_header_files "${ARG_SOURCE_DIRECTORY}/${ARG_COMPONENT_BASE}/${_component}.hpp")
    list(APPEND _module_source_files "${ARG_SOURCE_DIRECTORY}/${ARG_COMPONENT_BASE}/${_component}.cpp")

    set(_component_utest "${ARG_SOURCE_DIRECTORY}/${ARG_COMPONENT_BASE}/${_component}.utest.cpp")
    file(REAL_PATH "${_component_utest}" _component_utest_file BASE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
    if (EXISTS "${_component_utest_file}")
      set(component_utest_executable_target "${module_name}_utest_${_component}")

      add_executable(
          "${component_utest_executable_target}"
          "${_component_utest}"
      )
      set_target_properties(
          "${component_utest_executable_target}"
          PROPERTIES
          WSPACE_UTEST_COMPONENT "${_component}"
      )

      list(APPEND _module_utest_executable_targets "${component_utest_executable_target}")
    endif ()
  endforeach ()

  set(module_library_target "wspace_${module_name}")

  add_library(
      "${module_library_target}"
      ${_module_header_files}
      ${_module_source_files}
  )
  target_link_libraries(
      "${module_library_target}"
      PUBLIC ${ARG_LINK_PUBLIC}
  )
  target_include_directories(
      "${module_library_target}"
      PUBLIC "${ARG_SOURCE_DIRECTORY}"
  )
  foreach (module_name_to_link IN LISTS ARG_LINK_MODULE)
    target_link_libraries(
        "${module_library_target}"
        PUBLIC "wspace_${module_name_to_link}"
    )
  endforeach ()
  target_compile_features(
      "${module_library_target}"
      PUBLIC cxx_std_20
  )

  foreach (_utest_executable_target IN LISTS _module_utest_executable_targets)
    target_link_libraries(
        "${_utest_executable_target}"
        PRIVATE "${module_library_target}"
        PRIVATE gtest gmock gtest_main
    )
    get_target_property(_component "${_utest_executable_target}" WSPACE_UTEST_COMPONENT)
    add_test(NAME "${module_name}_utest_${_component}" COMMAND "${_utest_executable_target}")
  endforeach ()
endfunction()
