#ifndef WSPACE_BUFFER_BASE_HPP_373425813897465D9CE45404E664B340
#define WSPACE_BUFFER_BASE_HPP_373425813897465D9CE45404E664B340

#include <span>

#include <glad/glad.h>

namespace wspace::gfx::ogl {

class Buffer
{
public:
    Buffer();

    ~Buffer();

    [[nodiscard]] auto object() const -> GLuint;

protected:
    enum struct Target
    {
        Array,
        ElementArray,
    };

    [[nodiscard]] static auto as_gl_enum(Target target) -> GLenum;

    enum struct Usage
    {
        StaticDraw,
    };

    [[nodiscard]] static auto as_gl_enum(Usage usage) -> GLenum;

protected:
    void gl_bind_buffer(Target target) const;
    static void gl_buffer_data(Target target, std::span<const std::byte> bytes, Usage usage = Usage::StaticDraw);

private:
    GLuint _object;
};

class ArrayBuffer : public Buffer
{
public:
    void bind() const;
    void data(std::span<const std::byte> bytes, Usage usage = Usage::StaticDraw);
};

class ElementArrayBuffer : public Buffer
{
public:
    void bind() const;
    void data(std::span<const std::byte> bytes, Usage usage = Usage::StaticDraw);
};

} // namespace wspace::gfx::ogl

#endif // WSPACE_BUFFER_BASE_HPP_373425813897465D9CE45404E664B340
