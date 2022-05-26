#include "program.hpp"

#include "shader.hpp"

namespace wspace::gfx::ogl {

Program::Program()
{
    set_object(glCreateProgram());
}

Program::~Program()
{
    glDeleteProgram(object());
}

void Program::attach_shader(const Shader &shader)
{
    glAttachShader(object(), shader.object());
}

void Program::detach_shader(const Shader &shader)
{
    glDetachShader(object(), shader.object());
}

auto Program::get_attribute_location(const char *name) const -> GLuint
{
    return glGetAttribLocation(object(), name);
}

auto Program::get_uniform_location(const char *name) const -> GLuint
{
    return glGetUniformLocation(object(), name);
}

void Program::link()
{
    glLinkProgram(object());
}

void Program::use() const
{
    glUseProgram(object());
}

} // namespace wspace::gfx::ogl
