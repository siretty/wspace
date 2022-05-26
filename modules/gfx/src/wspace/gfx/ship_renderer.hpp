#ifndef WSPACE_SHIP_RENDERER_HPP_F2AD3510C59C4B098F3FB6E928A5CB9E
#define WSPACE_SHIP_RENDERER_HPP_F2AD3510C59C4B098F3FB6E928A5CB9E

#include "ogl/array.hpp"
#include "ogl/buffer.hpp"
#include "ogl/program.hpp"

#include <vector>

#include <glm/glm.hpp>

namespace wspace::gfx {

struct Ship
{
    glm::vec2 position;
    float angle;
};

class ShipRenderer
{
public:
    ShipRenderer();

    void clear_instances();
    void add_instance(const Ship &ship_instance);

    void update();

    void draw(const glm::mat4 &mvp);

private:
    std::vector<Ship> _instances;

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

#endif // WSPACE_SHIP_RENDERER_HPP_F2AD3510C59C4B098F3FB6E928A5CB9E
