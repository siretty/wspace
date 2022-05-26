#ifndef WSPACE_PROGRAM_HPP_33E7777F19B541EBA40650BC4035DE30
#define WSPACE_PROGRAM_HPP_33E7777F19B541EBA40650BC4035DE30

#include "object.hpp"

#include <glad/glad.h>

namespace wspace::gfx::ogl {

class Shader;

class Program : Object
{
public:
    Program();
    ~Program();

    void attach_shader(const Shader &shader);
    void detach_shader(const Shader &shader);

    [[nodiscard]] auto get_attribute_location(const char *name) const -> GLuint;
    [[nodiscard]] auto get_uniform_location(const char *name) const -> GLuint;

    void link();

    void use() const;
};

} // namespace wspace::gfx::ogl

#endif // WSPACE_PROGRAM_HPP_33E7777F19B541EBA40650BC4035DE30
