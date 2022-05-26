#ifndef WSPACE_ASTEROID_RENDERER_HPP_1D59FBE0D0354A99A734E21BBEAD2F06
#define WSPACE_ASTEROID_RENDERER_HPP_1D59FBE0D0354A99A734E21BBEAD2F06

#include "ogl/array.hpp"
#include "ogl/buffer.hpp"
#include "ogl/program.hpp"

#include <vector>

#include <glm/glm.hpp>

namespace wspace::gfx {

struct Asteroid
{
    glm::vec2 position;
};

class AsteroidRenderer
{
public:
    AsteroidRenderer();

    void clear_instances();
    void add_instance(const Asteroid &instance);

    void update();

    void draw(const glm::mat4 &mvp);

private:
    std::vector<Asteroid> _instances;

    GLuint _loc_un_mvp;
    ogl::Program _program;

    ogl::VertexArray _vertex_array;
    ogl::ArrayBuffer _vertex_attribute_buffer;
    ogl::ElementArrayBuffer _vertex_index_buffer;
    ogl::ArrayBuffer _instance_attribute_buffer;

    std::size_t _index_count = 0;
    std::size_t _instance_count = 0;
};

} // namespace wspace::gfx

#endif // WSPACE_ASTEROID_RENDERER_HPP_1D59FBE0D0354A99A734E21BBEAD2F06
