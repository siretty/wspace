#ifndef WSPACE_PLAYER_HPP_9611350873BC4D14B6FC97419FCEF25B
#define WSPACE_PLAYER_HPP_9611350873BC4D14B6FC97419FCEF25B

#include <wspace/affine_space.hpp>

#include <string_view>

namespace wspace {

class Player
{
public:
    auto get_name() -> std::string_view;

    auto get_position() const -> Point<double, 3>;
    void set_position(Point<double, 3> new_position);

    auto get_target_position() const -> Point<double, 3>;
    void set_target_position(Point<double, 3> new_target_position);

    auto get_speed() const -> double;
    void set_speed(double new_speed);

    void update(double delta_time);

private:
    Point<double, 3> _position;
    Point<double, 3> _target_position;

    double _speed;
};

} // namespace wspace

#endif // WSPACE_PLAYER_HPP_9611350873BC4D14B6FC97419FCEF25B
