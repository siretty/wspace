#include "object.hpp"

namespace wspace::gfx::ogl {

auto Object::object() const -> GLuint
{
    return _object.value();
}

void Object::set_object(GLuint object_)
{
    _object = object_;
}

} // namespace wspace::gfx::ogl
