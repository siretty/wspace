#include <wspace/gfx/asteroid_renderer.hpp>
#include <wspace/gfx/perspective_camera.hpp>
#include <wspace/gfx/ship_renderer.hpp>
#include <wspace/gfx/station_renderer.hpp>
#include <wspace/runtime/renderer.hpp>
#include <wspace/support/on_scope_exit.hpp>
#include <wspace/support/vector.hpp>

#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>

#include <cstdlib>

#include <entt/entt.hpp>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace {

extern "C"
{
    static void glfw_error_callback(int error, const char *description);
    static void glfw_key_callback(GLFWwindow *p_window, int key, int scancode, int action, int mods);
    static void glfw_window_focus_callback(GLFWwindow *p_window, int focused);

    static void GLAPIENTRY gl_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                               const GLchar *message, const void *user_param);
}

using GlfwWindowPtr = std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow *)>>;

auto create_glfw_window() -> GlfwWindowPtr;

void setup_glfw_window_callbacks(GLFWwindow *glfw_window_p);
void setup_glad(GLFWwindow *glfw_window_p);
auto setup_imgui(GLFWwindow *glfw_window_p) -> wspace::OnScopeExit<std::function<void()>>;

void imgui_begin_frame();
void imgui_end_frame();
void imgui_draw();

using Position = wspace::Vector2DT<struct PositionTag>;
using Velocity = wspace::Vector2DT<struct VelocityTag>;

struct OreProvider
{
    double available = 0.0;
};

struct OreContainer
{
    double stored = 0.0;
};

struct OreConsumer
{
    double consumed = 0.0;
};

struct Target
{
    entt::entity entity;
};

struct LineGraphics
{
    std::unique_ptr<wspace::ILineStrip> line_strip_p;
};

struct AsteroidGraphics
{
};

struct ShipGraphics
{
};

struct StationGraphics
{
};

} // namespace

int main()
{
    if (glfwInit() != GLFW_TRUE)
    {
        std::cerr << "glfwInit failed" << '\n';
        std::exit(EXIT_FAILURE);
    }

    const auto glfw_terminator = wspace::on_scope_exit([] { glfwTerminate(); });
    glfwSetErrorCallback(glfw_error_callback);

    const auto glfw_window_p = create_glfw_window();
    setup_glfw_window_callbacks(glfw_window_p.get());
    setup_glad(glfw_window_p.get());

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(gl_message_callback, nullptr);

    const auto imgui_terminator = setup_imgui(glfw_window_p.get());

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glPointSize(1);
    glLineWidth(1);

    glClearColor(.1f, .1f, .1f, 1.f);

    auto rng = std::mt19937_64(0);
    auto x_dis = std::uniform_real_distribution<double>(-15, 15);
    auto y_dis = std::uniform_real_distribution<double>(-15, 15);

    entt::registry registry;

    for (int i = 0; i < 1000; ++i)
    {
        const auto station = registry.create();
        registry.emplace<Position>(station) = Position(x_dis(rng), y_dis(rng));
        registry.emplace<OreConsumer>(station);
        registry.emplace<StationGraphics>(station);
    }

    for (int i = 0; i < 1000; ++i)
    {
        const auto asteroid = registry.create();
        registry.emplace<Position>(asteroid) = Position(x_dis(rng), y_dis(rng));
        registry.emplace<OreProvider>(asteroid).available = 500.0;
        registry.emplace<AsteroidGraphics>(asteroid);
    }

    for (int i = 0; i < 1000; ++i)
    {
        const auto player = registry.create();
        registry.emplace<Position>(player) = Position(x_dis(rng), y_dis(rng));
        registry.emplace<Velocity>(player) = Velocity(0, 0);
        registry.emplace<Target>(player).entity = entt::null;
        registry.emplace<OreContainer>(player);
        registry.emplace<ShipGraphics>(player);
    }

    wspace::gfx::AsteroidRenderer asteroid_renderer;
    wspace::gfx::ShipRenderer ship_renderer;
    wspace::gfx::StationRenderer station_renderer;

    wspace::gfx::PerspectiveCamera perspective_camera;
    perspective_camera.move_to({0, 0, 30});
    // perspective_camera.look_to({0, 0, -1}, {0, 1, 0});

    double frame_start_time = glfwGetTime(), frame_time = 0.0;

    while (glfwWindowShouldClose(glfw_window_p.get()) == GLFW_FALSE)
    {
        glfwPollEvents();

        imgui_begin_frame();

        ImGui::Begin("wspace");
        {
            if (ImGui::Button("Quit"))
            {
                glfwSetWindowShouldClose(glfw_window_p.get(), GLFW_TRUE);
            }

            ImGui::Text("Frame time: %.3f ms (%.1f FPS)", 1000.0 * frame_time, 1.0 / frame_time);

            for (const auto view = registry.view<OreProvider>(); const auto entity : view)
            {
                const auto [provider] = view.get(entity);
                ImGui::Text("Provider: %f", provider.available);
            }

            for (const auto view = registry.view<OreContainer>(); const auto entity : view)
            {
                const auto [container] = view.get(entity);
                ImGui::Text("Container: %f", container.stored);
            }

            for (const auto view = registry.view<OreConsumer>(); const auto entity : view)
            {
                const auto [consumer] = view.get(entity);
                ImGui::Text("Consumer: %f", consumer.consumed);
            }
        }
        ImGui::End();

        imgui_end_frame();

        int width, height;
        glfwGetFramebufferSize(glfw_window_p.get(), &width, &height);

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 transform_model = glm::mat4(1.0f);

        const auto transform_view = perspective_camera.compute_transform();

        glm::mat4 transform_projection =
            glm::perspective(glm::radians(60.f), float(width) / float(height), float(0.01), float(1000.0));

        asteroid_renderer.clear_instances();
        for (const auto view = registry.view<AsteroidGraphics, Position>(); const auto entity : view)
        {
            const auto &x = view.get<Position>(entity);
            asteroid_renderer.add_instance({.position{x[0], x[1]}});
        }
        asteroid_renderer.update();

        ship_renderer.clear_instances();
        for (const auto view = registry.view<ShipGraphics, Position, Velocity>(); const auto entity : view)
        {
            const auto [x, v] = view.get<Position, Velocity>(entity);
            const auto angle = float(std::atan2(v[1], v[0]));
            ship_renderer.add_instance({.position{x[0], x[1]}, .angle = angle});
        }
        ship_renderer.update();

        station_renderer.clear_instances();
        for (const auto view = registry.view<StationGraphics, Position>(); const auto entity : view)
        {
            const auto &x = view.get<Position>(entity);
            station_renderer.add_instance({.position{x[0], x[1]}});
        }
        station_renderer.update();

        const auto mvp = transform_projection * transform_view * transform_model;
        asteroid_renderer.draw(mvp);
        ship_renderer.draw(mvp);
        station_renderer.draw(mvp);

        imgui_draw();
        glfwSwapBuffers(glfw_window_p.get());

        // UPDATES

        for (const auto view = registry.view<Position, Velocity, Target>(); const auto entity : view)
        {
            auto [position, velocity, target] = view.get(entity);

            if (target.entity == entt::null)
            {
                std::ranges::sample(registry.view<AsteroidGraphics>(), &target.entity, 1, rng);
            }

            const auto target_position = registry.get<Position>(target.entity);

            const auto delta_position = target_position - position;
            const auto distance_to_target = magnitude(delta_position);

            const auto speed = 10.;
            velocity =
                std::sqrt(std::min(speed * distance_to_target, speed)) * normalized_or_zero(target_position - position);

            if (distance_to_target < 0.1)
            {
                if (registry.any_of<StationGraphics>(target.entity))
                {
                    std::ranges::sample(registry.view<AsteroidGraphics>(), &target.entity, 1, rng);
                }
                else if (registry.any_of<AsteroidGraphics>(target.entity))
                {
                    std::ranges::sample(registry.view<StationGraphics>(), &target.entity, 1, rng);
                }
            }
        }

        for (const auto view = registry.view<OreContainer, Position, Target>(); const auto entity : view)
        {
            const auto [container, x, target] = view.get(entity);
            if (!registry.valid(target.entity) || !registry.all_of<Position>(target.entity))
            {
                continue;
            }

            const auto distance_to_target = magnitude(registry.get<Position>(target.entity) - x);
            if (distance_to_target > 0.5)
            {
                continue;
            }

            if (registry.all_of<OreConsumer>(target.entity))
            {
                auto &consumer = registry.get<OreConsumer>(target.entity);

                const auto amount = std::min((1. / 60.) * 1000., container.stored);

                container.stored -= amount;
                consumer.consumed += amount;
            }

            if (registry.all_of<OreProvider>(target.entity))
            {
                auto &provider = registry.get<OreProvider>(target.entity);

                const auto amount = std::min((1. / 60.) * 1000., provider.available);

                provider.available -= amount;
                container.stored += amount;
            }
        }

        for (const auto view = registry.view<Position, Velocity>(); const auto entity : view)
        {
            auto [position, velocity] = view.get(entity);
            position += (1. / 60.) * velocity;
        }

        double frame_end_time = glfwGetTime();
        frame_time = frame_end_time - frame_start_time;
        frame_start_time = frame_end_time;

        const float fly_speed = 50.f;
        if (glfwGetKey(glfw_window_p.get(), GLFW_KEY_W) == GLFW_PRESS)
        {
            perspective_camera.translate((fly_speed * 1.f / 60.f) * perspective_camera.get_forward());
        }
        if (glfwGetKey(glfw_window_p.get(), GLFW_KEY_S) == GLFW_PRESS)
        {
            perspective_camera.translate((fly_speed * 1.f / 60.f) * perspective_camera.get_reverse());
        }
        if (glfwGetKey(glfw_window_p.get(), GLFW_KEY_E) == GLFW_PRESS)
        {
            perspective_camera.translate((fly_speed * 1.f / 60.f) * perspective_camera.get_up());
        }
        if (glfwGetKey(glfw_window_p.get(), GLFW_KEY_Q) == GLFW_PRESS)
        {
            perspective_camera.translate((fly_speed * 1.f / 60.f) * perspective_camera.get_down());
        }
        if (glfwGetKey(glfw_window_p.get(), GLFW_KEY_A) == GLFW_PRESS)
        {
            perspective_camera.translate((fly_speed * 1.f / 60.f) * perspective_camera.get_left());
        }
        if (glfwGetKey(glfw_window_p.get(), GLFW_KEY_D) == GLFW_PRESS)
        {
            perspective_camera.translate((fly_speed * 1.f / 60.f) * perspective_camera.get_right());
        }

        const float rotate_speed = 0.5f;
        if (glfwGetKey(glfw_window_p.get(), GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            perspective_camera.rotate(-rotate_speed * 1.f / 60.f, perspective_camera.get_up());
        }
        if (glfwGetKey(glfw_window_p.get(), GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            perspective_camera.rotate(+rotate_speed * 1.f / 60.f, perspective_camera.get_up());
        }
        if (glfwGetKey(glfw_window_p.get(), GLFW_KEY_UP) == GLFW_PRESS)
        {
            perspective_camera.rotate(-rotate_speed * 1.f / 60.f, perspective_camera.get_right());
        }
        if (glfwGetKey(glfw_window_p.get(), GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            perspective_camera.rotate(+rotate_speed * 1.f / 60.f, perspective_camera.get_right());
        }

        //        on_update(frame_time);
    }
}

namespace {

extern "C"
{
    static void glfw_error_callback(int error, const char *description)
    {
        std::fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
    }

    static void glfw_key_callback(GLFWwindow *p_window, int key, int scancode, int action, int mods)
    {
        (void)p_window, (void)key, (void)scancode, (void)action, (void)mods;

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(p_window, GLFW_TRUE);
        }

        //        if (key == GLFW_KEY_F && (action == GLFW_PRESS || action == GLFW_REPEAT))
        //        {
        //            if (on_emit_key_pressed)
        //            {
        //                on_emit_key_pressed();
        //            }
        //        }
        //
        //        switch (key)
        //        {
        //        case GLFW_KEY_W:
        //            camera_controller.move_forward(action == GLFW_PRESS || action == GLFW_REPEAT);
        //            break;
        //        case GLFW_KEY_S:
        //            camera_controller.move_reverse(action == GLFW_PRESS || action == GLFW_REPEAT);
        //            break;
        //        case GLFW_KEY_A:
        //            camera_controller.move_left(action == GLFW_PRESS || action == GLFW_REPEAT);
        //            break;
        //        case GLFW_KEY_D:
        //            camera_controller.move_right(action == GLFW_PRESS || action == GLFW_REPEAT);
        //            break;
        //        case GLFW_KEY_E:
        //            camera_controller.move_up(action == GLFW_PRESS || action == GLFW_REPEAT);
        //            break;
        //        case GLFW_KEY_Q:
        //            camera_controller.move_down(action == GLFW_PRESS || action == GLFW_REPEAT);
        //            break;
        //        case GLFW_KEY_U:
        //            camera_controller.roll_left(action == GLFW_PRESS || action == GLFW_REPEAT);
        //            break;
        //        case GLFW_KEY_O:
        //            camera_controller.roll_right(action == GLFW_PRESS || action == GLFW_REPEAT);
        //            break;
        //        case GLFW_KEY_I:
        //            camera_controller.pitch_up(action == GLFW_PRESS || action == GLFW_REPEAT);
        //            break;
        //        case GLFW_KEY_K:
        //            camera_controller.pitch_down(action == GLFW_PRESS || action == GLFW_REPEAT);
        //            break;
        //        case GLFW_KEY_J:
        //            camera_controller.yaw_left(action == GLFW_PRESS || action == GLFW_REPEAT);
        //            break;
        //        case GLFW_KEY_L:
        //            camera_controller.yaw_right(action == GLFW_PRESS || action == GLFW_REPEAT);
        //            break;
        //        default:
        //            break;
        //        }
    }

    static void glfw_window_focus_callback(GLFWwindow *p_window, int focused)
    {
        //        if (focused == GLFW_FALSE)
        //        {
        //            camera_controller.reset();
        //        }
    }

    static void GLAPIENTRY gl_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                               const GLchar *message, const void *user_param)
    {

        std::fprintf(stderr, "OpenGL Message: %s\n", message);
    }
}

auto create_glfw_window() -> GlfwWindowPtr
{
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return GlfwWindowPtr{glfwCreateWindow(1920, 1080, "wspace", nullptr, nullptr), glfwDestroyWindow};
}

void setup_glfw_window_callbacks(GLFWwindow *glfw_window_p)
{
    glfwSetKeyCallback(glfw_window_p, glfw_key_callback);
    glfwSetWindowFocusCallback(glfw_window_p, glfw_window_focus_callback);
}

void setup_glad(GLFWwindow *glfw_window_p)
{
    glfwMakeContextCurrent(glfw_window_p);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::fprintf(stderr, "gladLoadGLLoader failed\n");
        std::exit(EXIT_FAILURE);
    }
}

auto setup_imgui(GLFWwindow *glfw_window_p) -> wspace::OnScopeExitFunction
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Enable docking
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // Disable multiple viewports (broken on native Wayland, e.g. using glfw-wayland)
    ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(glfw_window_p, true);
    ImGui_ImplOpenGL3_Init("#version 400");

    return wspace::on_scope_exit_function([] {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    });
}

void imgui_begin_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void imgui_end_frame()
{
    ImGui::Render();
}

void imgui_draw()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

} // namespace
