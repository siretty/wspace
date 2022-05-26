#ifndef WSPACE_SHADER_HPP_515D73B87DF040E4B37FB43F3E39B6D9
#define WSPACE_SHADER_HPP_515D73B87DF040E4B37FB43F3E39B6D9

#include "object.hpp"

#include <span>
#include <string_view>

#include <glad/glad.h>

namespace wspace::gfx::ogl {

class Shader : public Object
{
public:
    enum struct Type
    {
        Vertex,
        Fragment,

        // Compute,
        // TesslationControl,
        // TesslationEvaluation,
        // Geometry,
    };

    static auto as_gl_enum(Type type) -> GLenum;

    explicit Shader(Type type);

    ~Shader();

    void source(std::span<const std::string_view> sources);
    void source(std::string_view source_);

    void compile();
};

class VertexShader : public Shader
{
public:
    VertexShader();
};

class FragmentShader : public Shader
{
public:
    FragmentShader();
};

} // namespace wspace::gfx::ogl

#endif // WSPACE_SHADER_HPP_515D73B87DF040E4B37FB43F3E39B6D9
