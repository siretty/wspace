
add_executable(
    wspace-client
    main.cpp
)
target_link_libraries(
    wspace-client
    PRIVATE wspace_model
)
set_target_properties(
    wspace-client PROPERTIES
    CXX_STANDARD 20
)
