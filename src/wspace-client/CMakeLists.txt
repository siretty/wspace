
add_executable(
    wspace-client
    wspace-client.cpp
)
target_link_libraries(
    wspace-client
    PRIVATE wspace_runtime
    PRIVATE wspace_gfx
    PRIVATE asio
    PRIVATE EnTT::EnTT
    PRIVATE glfw
    PRIVATE glad
    PRIVATE imgui
)
