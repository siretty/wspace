#ifndef WSPACE_ARRAY_HPP_376748D10B80468CA14DBD53BCA5BEAA
#define WSPACE_ARRAY_HPP_376748D10B80468CA14DBD53BCA5BEAA

#include "object.hpp"

#include <glad/glad.h>

namespace wspace::gfx::ogl {

class VertexArray : public Object
{
public:
    VertexArray();

    ~VertexArray();

    void bind() const;

    void enable_attribute(GLuint index);
    void disable_attribute(GLuint index);
};

struct VertexAttribute
{
    enum struct Type
    {
        Float,
    };

    static auto as_gl_enum(Type type) -> GLenum;

    std::size_t size;
    Type type;
    bool normalized;
    std::size_t stride;
    std::size_t offset;

    void define(GLuint index) const;
};

} // namespace wspace::gfx::ogl

#endif // WSPACE_ARRAY_HPP_376748D10B80468CA14DBD53BCA5BEAA
