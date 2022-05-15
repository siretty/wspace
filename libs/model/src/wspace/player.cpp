#include "player.hpp"

namespace wspace {

auto Player::get_name() -> std::string_view
{
    return "Tim Berman";
}

auto Player::get_position() const -> Point<double, 3>
{
    return _position;
}

void Player::set_position(Point<double, 3> new_position)
{
    _position = new_position;
}

auto Player::get_target_position() const -> Point<double, 3>
{
    return _target_position;
}

void Player::set_target_position(Point<double, 3> new_target_position)
{
    _target_position = new_target_position;
}

auto Player::get_speed() const -> double
{
    return _speed;
}

void Player::set_speed(double new_speed)
{
    _speed = new_speed;
}

void Player::update(double delta_time)
{
    _position += _speed * normalize_or_zero(_target_position - _position);
}

} // namespace wspace
