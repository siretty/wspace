#ifndef WSPACE_OBJECT_HPP_471467321D3C4DE68CED098806EB95D2
#define WSPACE_OBJECT_HPP_471467321D3C4DE68CED098806EB95D2

#include <optional>

#include <glad/glad.h>

namespace wspace::gfx::ogl {

class Object
{
public:
    Object() = default;

    Object(Object &&other) noexcept = default;
    Object &operator=(Object &&other) noexcept = default;

    Object(const Object &) = delete;
    Object &operator=(const Object &) = delete;

    auto object() const -> GLuint;

protected:
    void set_object(GLuint object_);

private:
    std::optional<GLuint> _object;
};

} // namespace wspace::gfx::ogl

#endif // WSPACE_OBJECT_HPP_471467321D3C4DE68CED098806EB95D2
