#include "renderer.hpp"
#include <wspace/gfx/ogl/array.hpp>
#include <wspace/gfx/ogl/buffer.hpp>
#include <wspace/gfx/ogl/program.hpp>
#include <wspace/gfx/ogl/shader.hpp>

#include <optional>
#include <vector>

#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

namespace {

using wspace::gfx::ogl::FragmentShader;
using wspace::gfx::ogl::Program;
using wspace::gfx::ogl::Shader;
using wspace::gfx::ogl::VertexShader;

void load_shader(Shader &shader, const std::string &source);
void load_shader_program(Program &program, const VertexShader &vertex_shader, const FragmentShader &fragment_shader);

auto line_vertex_shader_source() -> const std::string &;
auto line_fragment_shader_source() -> const std::string &;

} // namespace

namespace wspace {

struct LineStrip : public ILineStrip
{
    std::size_t vertex_count;

    gfx::ogl::VertexArray vao;
    gfx::ogl::ArrayBuffer vbo;

    gfx::ogl::Program shader_program;

    struct
    {
        GLuint model;
        GLuint view;
        GLuint projection;
    } uniform_loc;
};

std::unique_ptr<ILineStrip> make_line_strip(std::span<LineVertex> line_vertices)
{
    auto line_strip_p = std::make_unique<LineStrip>();

    auto vertex_shader = VertexShader();
    load_shader(vertex_shader, line_vertex_shader_source());

    auto fragment_shader = FragmentShader();
    load_shader(fragment_shader, line_fragment_shader_source());

    load_shader_program(line_strip_p->shader_program, vertex_shader, fragment_shader);

    {
        int position_loc = line_strip_p->shader_program.get_attribute_location("va_position");
        int color_loc = line_strip_p->shader_program.get_attribute_location("va_color");

        line_strip_p->uniform_loc.model = line_strip_p->shader_program.get_uniform_location("model");
        line_strip_p->uniform_loc.view = line_strip_p->shader_program.get_uniform_location("view");
        line_strip_p->uniform_loc.projection = line_strip_p->shader_program.get_uniform_location("projection");

        line_strip_p->vao.bind();
        line_strip_p->vao.enable_attribute(position_loc);
        line_strip_p->vao.enable_attribute(color_loc);

        line_strip_p->vbo.bind();
        glVertexAttribPointer(position_loc, 2, GL_FLOAT, GL_FALSE, sizeof(LineVertex),
                              reinterpret_cast<void *>(std::uintptr_t(offsetof(LineVertex, position))));
        glVertexAttribPointer(color_loc, 4, GL_FLOAT, GL_FALSE, sizeof(LineVertex),
                              reinterpret_cast<void *>(std::uintptr_t(offsetof(LineVertex, color))));
    }

    {
        line_strip_p->vertex_count = line_vertices.size();

        line_strip_p->vao.bind();

        line_strip_p->vbo.bind();
        line_strip_p->vbo.data(as_bytes(line_vertices));
    }

    return line_strip_p;
}

void draw_line_strip(const ILineStrip &i_line_strip, const glm::mat4 &model, const glm::mat4 &view,
                     const glm::mat4 &projection)
{
    const auto &line_strip = static_cast<const LineStrip &>(i_line_strip);

    line_strip.shader_program.use();

    glUniformMatrix4fv(line_strip.uniform_loc.model, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(line_strip.uniform_loc.view, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(line_strip.uniform_loc.projection, 1, GL_FALSE, glm::value_ptr(projection));

    line_strip.vao.bind();
    glDrawArrays(GL_LINE_STRIP, 0, line_strip.vertex_count);
}

} // namespace wspace

namespace {

void load_shader(Shader &shader, const std::string &source)
{
    const auto sources = {std::string_view(source)};
    shader.source(sources);
    shader.compile();
}

void load_shader_program(Program &program, const VertexShader &vertex_shader, const FragmentShader &fragment_shader)
{
    program.attach_shader(vertex_shader);
    // if (geometry_shader.has_value())
    //{
    //     glAttachShader(shader_program, geometry_shader.value());
    // }
    program.attach_shader(fragment_shader);

    program.link();

    program.detach_shader(vertex_shader);
    program.detach_shader(fragment_shader);

    // if (geometry_shader.has_value())
    //{
    //     glDetachShader(shader_program, geometry_shader.value());
    //     glDeleteShader(geometry_shader.value());
    // }
}

auto line_vertex_shader_source() -> const std::string &
{
    static auto source = std::string{R"raw(
#version 400

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

attribute vec2 va_position;
attribute vec4 va_color;

out vec4 vertex_color;

void main() {
    gl_Position = projection * (view * (model * vec4(va_position, -30.0, 1.0)));
    vertex_color = va_color;
}
)raw"};
    return source;
}

auto line_fragment_shader_source() -> const std::string &
{
    static auto source = std::string{R"raw(
#version 400

in vec4 vertex_color;

layout (location = 0) out vec4 fragment_color;

void main() {
    fragment_color = vertex_color;
}
)raw"};
    return source;
}

} // namespace
