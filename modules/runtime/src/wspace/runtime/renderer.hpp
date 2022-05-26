#ifndef WSPACE_RENDERER_HPP_6F88A12947DF4C098028C226A69FAC73
#define WSPACE_RENDERER_HPP_6F88A12947DF4C098028C226A69FAC73

#include <memory>
#include <span>

#include <glm/glm.hpp>

namespace wspace {

struct LineVertex
{
    glm::vec2 position;
    glm::vec4 color;
};

struct ILineStrip
{
    virtual ~ILineStrip() = default;
};

std::unique_ptr<ILineStrip> make_line_strip(std::span<LineVertex> line_vertices);

void draw_line_strip(const ILineStrip &line_strip, const glm::mat4 &model, const glm::mat4 &view,
                     const glm::mat4 &projection);

} // namespace wspace

#endif // WSPACE_RENDERER_HPP_6F88A12947DF4C098028C226A69FAC73
