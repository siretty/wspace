#include "station_renderer.hpp"

#include "ogl/buffer.hpp"
#include "ogl/shader.hpp"

#include <string_view>

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace {

struct Data
{
    struct Vertex
    {
        glm::vec2 position;
        glm::vec4 color;
    };

    static auto vertices() -> std::span<const Vertex>;
    static auto indices() -> std::span<const GLushort>;

    static std::string_view vertex_shader;
    static std::string_view fragment_shader;
};

} // namespace

namespace wspace::gfx {

StationRenderer::StationRenderer()
{
    // shaders
    {
        ogl::VertexShader vertex_shader;
        vertex_shader.source(Data::vertex_shader);

        ogl::FragmentShader fragment_shader;
        fragment_shader.source(Data::fragment_shader);

        vertex_shader.compile();
        fragment_shader.compile();

        _program.attach_shader(vertex_shader);
        _program.attach_shader(fragment_shader);

        _program.link();

        _program.detach_shader(vertex_shader);
        _program.detach_shader(fragment_shader);

        _loc_un_mvp = _program.get_uniform_location("un_mvp");
    }

    const auto loc_va_position = _program.get_attribute_location("va_position");
    const auto loc_va_color = _program.get_attribute_location("va_color");

    // vertices
    {
        const auto raw_indices = Data::indices();

        _index_count = raw_indices.size();

        _vertex_array.bind();

        _vertex_index_buffer.bind();
        _vertex_index_buffer.data(as_bytes(raw_indices));

        _vertex_attribute_buffer.bind();
        _vertex_attribute_buffer.data(as_bytes(Data::vertices()));

        glEnableVertexAttribArray(loc_va_position);
        glVertexAttribDivisor(loc_va_position, 0);
        glVertexAttribPointer(loc_va_position, 2, GL_FLOAT, GL_FALSE, sizeof(Data::Vertex),
                              reinterpret_cast<const void *>(std::uintptr_t(offsetof(Data::Vertex, position))));

        glEnableVertexAttribArray(loc_va_color);
        glVertexAttribDivisor(loc_va_color, 0);
        glVertexAttribPointer(loc_va_color, 4, GL_FLOAT, GL_FALSE, sizeof(Data::Vertex),
                              reinterpret_cast<const void *>(std::uintptr_t(offsetof(Data::Vertex, color))));
    }
}

void StationRenderer::clear_instances()
{
    _instances.clear();
}

void StationRenderer::add_instance(const Station &instance)
{
    _instances.emplace_back(instance);
}

void StationRenderer::update()
{
    const auto loc_in_position = _program.get_attribute_location("in_position");
    const auto loc_in_angle = _program.get_attribute_location("in_angle");

    _vertex_array.bind();

    _instance_attribute_buffer.bind();
    _instance_attribute_buffer.data(as_bytes(std::span{_instances}));

    glEnableVertexAttribArray(loc_in_position);
    glVertexAttribDivisor(loc_in_position, 1);
    glVertexAttribPointer(loc_in_position, 2, GL_FLOAT, GL_FALSE, sizeof(Station),
                          reinterpret_cast<const void *>(std::uintptr_t(offsetof(Station, position))));

    _instance_count = _instances.size();
}

void StationRenderer::draw(const glm::mat4 &mvp)
{
    _program.use();

    glUniformMatrix4fv(_loc_un_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

    _vertex_array.bind();
    glDrawElementsInstanced(GL_LINE_STRIP, _index_count, GL_UNSIGNED_SHORT, nullptr, _instance_count);
}

} // namespace wspace::gfx

namespace {

using namespace std::string_view_literals;

auto Data::vertices() -> std::span<const Vertex>
{
    static constexpr std::initializer_list<const Vertex> vertices = {
        {.position = glm::vec2(-1, -1), .color = glm::vec4(1, 0, 0, 1)},
        {.position = glm::vec2(+1, -1), .color = glm::vec4(1, 1, 0, 1)},
        {.position = glm::vec2(+1, +1), .color = glm::vec4(0, 1, 0, 1)},
        {.position = glm::vec2(-1, +1), .color = glm::vec4(0, 1, 1, 1)},
    };
    return {vertices};
}

auto Data::indices() -> std::span<const GLushort>
{
    static constexpr std::initializer_list<const GLushort> indices = {0, 1, 2, 3, 0};
    return {indices};
}

std::string_view Data::vertex_shader{R"glsl(
#version 400

uniform mat4 un_mvp;

attribute vec2 va_position;
attribute vec4 va_color;

attribute vec2 in_position;
attribute float in_angle;

out vec4 vertex_color;

void main() {
    gl_Position = un_mvp * vec4(0.1 * va_position + in_position, -30.0, 1.0);
    vertex_color = va_color;
}
)glsl"};

std::string_view Data::fragment_shader{R"glsl(
#version 400

in vec4 vertex_color;

layout (location = 0) out vec4 fragment_color;

void main() {
    fragment_color = vertex_color;
}
)glsl"};

} // namespace
