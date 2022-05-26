#ifndef WSPACE_STATION_RENDERER_HPP_568B8AE5F8B9446BA3997DDC3865672F
#define WSPACE_STATION_RENDERER_HPP_568B8AE5F8B9446BA3997DDC3865672F

#include "ogl/array.hpp"
#include "ogl/buffer.hpp"
#include "ogl/program.hpp"

#include <vector>

#include <glm/glm.hpp>

namespace wspace::gfx {

struct Station
{
    glm::vec2 position;
};

class StationRenderer
{
public:
    StationRenderer();

    void clear_instances();
    void add_instance(const Station &instance);

    void update();

    void draw(const glm::mat4 &mvp);

private:
    std::vector<Station> _instances;

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

#endif // WSPACE_STATION_RENDERER_HPP_568B8AE5F8B9446BA3997DDC3865672F
