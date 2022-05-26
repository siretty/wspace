#include "shader.hpp"

#include <vector>

#include <cstdlib>

namespace wspace::gfx::ogl {

auto Shader::as_gl_enum(const Type type) -> GLenum
{
    switch (type)
    {
    case Type::Vertex:
        return GL_VERTEX_SHADER;
    case Type::Fragment:
        return GL_FRAGMENT_SHADER;
    }
    std::abort();
}

Shader::Shader(const Type type)
{
    set_object(glCreateShader(as_gl_enum(type)));
}

Shader::~Shader()
{
    glDeleteShader(object());
}

void Shader::source(const std::span<const std::string_view> sources)
{
    std::vector<const GLchar *> strings;
    std::vector<GLint> lengths;

    for (const auto &source_code : sources)
    {
        strings.emplace_back(source_code.data());
        lengths.emplace_back(source_code.size());
    }

    glShaderSource(object(), sources.size(), strings.data(), lengths.data());
}

void Shader::source(const std::string_view source_)
{
    source(std::array<std::string_view, 1>{source_});
}

void Shader::compile()
{
    glCompileShader(object());
}

VertexShader::VertexShader() : Shader(Type::Vertex)
{
}

FragmentShader::FragmentShader() : Shader(Type::Fragment)
{
}

} // namespace wspace::gfx::ogl
