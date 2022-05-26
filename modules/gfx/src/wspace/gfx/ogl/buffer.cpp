#include "buffer.hpp"

#include <cstdlib>

namespace wspace::gfx::ogl {

Buffer::Buffer()
{
    glGenBuffers(1, &_object);
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &_object);
}

auto Buffer::object() const -> GLuint
{
    return _object;
}

auto Buffer::as_gl_enum(const Target target) -> GLenum
{
    switch (target)
    {
    case Target::Array:
        return GL_ARRAY_BUFFER;
    case Target::ElementArray:
        return GL_ELEMENT_ARRAY_BUFFER;
    }
    std::abort();
}

auto Buffer::as_gl_enum(const Usage usage) -> GLenum
{
    switch (usage)
    {
    case Usage::StaticDraw:
        return GL_STATIC_DRAW;
    }
    std::abort();
}

void Buffer::gl_bind_buffer(const Target target) const
{
    glBindBuffer(as_gl_enum(target), _object);
}

void Buffer::gl_buffer_data(const Target target, std::span<const std::byte> bytes, const Usage usage)
{
    glBufferData(as_gl_enum(target), bytes.size(), bytes.data(), as_gl_enum(usage));
}

void ArrayBuffer::bind() const
{
    gl_bind_buffer(Target::Array);
}

void ArrayBuffer::data(std::span<const std::byte> bytes, const Usage usage)
{
    gl_buffer_data(Target::Array, bytes, usage);
}

void ElementArrayBuffer::bind() const
{
    gl_bind_buffer(Target::ElementArray);
}

void ElementArrayBuffer::data(std::span<const std::byte> bytes, const Usage usage)
{
    gl_buffer_data(Target::ElementArray, bytes, usage);
}

} // namespace wspace::gfx::ogl
