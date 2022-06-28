
# ============================================================
# ASIO
# ============================================================

add_library(asio INTERFACE)
target_include_directories(asio INTERFACE asio/asio/include)

# ============================================================
# EnTT
# ============================================================

add_subdirectory(entt EXCLUDE_FROM_ALL)

# ============================================================
# GLAD
# ============================================================

add_library(
    glad
    glad/src/glad.c
    glad/include/glad/glad.h
    glad/include/KHR/khrplatform.h
)
target_include_directories(glad PUBLIC glad/include)

# ============================================================
# GLFW
# ============================================================

add_subdirectory(glfw EXCLUDE_FROM_ALL)

# ============================================================
# GLM
# ============================================================

add_subdirectory(glm EXCLUDE_FROM_ALL)

# ============================================================
# Google Test & Mock
# ============================================================

add_subdirectory(googletest EXCLUDE_FROM_ALL)

# ============================================================
# ImGUI
# ============================================================

add_library(
    imgui STATIC
    imgui/imgui.h
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_internal.h
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.h
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.h
    imgui/backends/imgui_impl_opengl3_loader.h
    imgui/backends/imgui_impl_opengl3.cpp
    imgui/imgui_demo.cpp
)
target_include_directories(imgui PUBLIC imgui)
target_include_directories(imgui PUBLIC imgui/backends)
target_link_libraries(imgui PUBLIC glfw)
