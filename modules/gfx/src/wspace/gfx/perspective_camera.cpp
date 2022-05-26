#include "perspective_camera.hpp"

#include <glm/gtc/quaternion.hpp>

namespace wspace::gfx {

void PerspectiveCamera::move_to(glm::vec3 new_position)
{
    _position = new_position;
}

void PerspectiveCamera::look_to(glm::vec3 forward, glm::vec3 up)
{
    const auto project = [](const auto u, const auto v) { return (glm::dot(u, v) / glm::dot(u, u)) * u; };

    _forward = glm::normalize(forward);
    _up = glm::normalize(up - project(_forward, up));
    _right = glm::cross(_forward, _up);
}

void PerspectiveCamera::translate(glm::vec3 delta_x)
{
    _position += delta_x;
}

void PerspectiveCamera::rotate(float angle, glm::vec3 axis)
{
    const auto q = glm::angleAxis(angle, axis);
    _forward = conjugate(q) * _forward * q;
    _up = conjugate(q) * _up * q;
    _right = conjugate(q) * _right * q;
}

auto PerspectiveCamera::get_forward() const -> glm::vec3
{
    return _forward;
}

auto PerspectiveCamera::get_reverse() const -> glm::vec3
{
    return -_forward;
}

auto PerspectiveCamera::get_up() const -> glm::vec3
{
    return _up;
}

auto PerspectiveCamera::get_down() const -> glm::vec3
{
    return -_up;
}

auto PerspectiveCamera::get_left() const -> glm::vec3
{
    return -_right;
}

auto PerspectiveCamera::get_right() const -> glm::vec3
{
    return _right;
}

auto PerspectiveCamera::compute_transform() -> glm::mat4
{
    return glm::lookAt(_position, _position + _forward, _up);
}

} // namespace wspace::gfx
