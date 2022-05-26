#ifndef WSPACE_PERSPECTIVE_CAMERA_HPP_498C319F14B54451A5FA5A779CFD095D
#define WSPACE_PERSPECTIVE_CAMERA_HPP_498C319F14B54451A5FA5A779CFD095D

#include <glm/glm.hpp>

namespace wspace::gfx {

class PerspectiveCamera
{
public:
    void move_to(glm::vec3 new_position);
    void look_to(glm::vec3 forward, glm::vec3 up);

    void translate(glm::vec3 delta_x);
    void rotate(float angle, glm::vec3 axis);

    [[nodiscard]] auto get_forward() const -> glm::vec3;
    [[nodiscard]] auto get_reverse() const -> glm::vec3;
    [[nodiscard]] auto get_up() const -> glm::vec3;
    [[nodiscard]] auto get_down() const -> glm::vec3;
    [[nodiscard]] auto get_left() const -> glm::vec3;
    [[nodiscard]] auto get_right() const -> glm::vec3;

    [[nodiscard]] auto compute_transform() -> glm::mat4;

private:
    glm::vec3 _position = glm::vec3(0, 0, 0);
    glm::vec3 _forward = glm::vec3(0, 0, -1);
    glm::vec3 _up = glm::vec3(0, 1, 0);
    glm::vec3 _right = glm::cross(_forward, _up);
};

} // namespace wspace::gfx

#endif // WSPACE_PERSPECTIVE_CAMERA_HPP_498C319F14B54451A5FA5A779CFD095D
