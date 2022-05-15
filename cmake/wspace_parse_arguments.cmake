
macro(wspace_parse_arguments prefix caller_arguments)
  cmake_parse_arguments(
      WSPACE_PARSE_ARGUMENTS
      ""
      ""
      "_OPTION;_OVALUE;_MVALUE"
      ${ARGN}
  )

  cmake_parse_arguments(
      ${prefix}
      "${WSPACE_PARSE_ARGUMENTS__OPTION}"
      "${WSPACE_PARSE_ARGUMENTS__OVALUE}"
      "${WSPACE_PARSE_ARGUMENTS__MVALUE}"
      ${caller_arguments}
  )

  unset(WSPACE_PARSE_ARGUMENTS__OPTION)
  unset(WSPACE_PARSE_ARGUMENTS__OVALUE)
  unset(WSPACE_PARSE_ARGUMENTS__MVALUE)
endmacro()
