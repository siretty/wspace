#include "array.hpp"

#include <cstdint>
#include <cstdlib>

namespace wspace::gfx::ogl {

VertexArray::VertexArray()
{
    GLuint object_;
    glGenVertexArrays(1, &object_);
    set_object(object_);
}

VertexArray::~VertexArray()
{
    GLuint object_ = object();
    glDeleteVertexArrays(1, &object_);
}

void VertexArray::bind() const
{
    glBindVertexArray(object());
}

void VertexArray::enable_attribute(GLuint index)
{
    glEnableVertexAttribArray(index);
}

void VertexArray::disable_attribute(GLuint index)
{
    glDisableVertexAttribArray(index);
}

auto VertexAttribute::as_gl_enum(const Type type) -> GLenum
{
    switch (type)
    {
    case Type::Float:
        return GL_FLOAT;
    }
    std::abort();
}

void VertexAttribute::define(GLuint index) const
{
    glVertexAttribPointer(index, GLint(size), as_gl_enum(type), normalized ? GL_TRUE : GL_FALSE, GLsizei(stride),
                          reinterpret_cast<const void *>(static_cast<std::uintptr_t>(offset)));
}

} // namespace wspace::gfx::ogl
