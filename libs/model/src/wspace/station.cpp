#include "station.hpp"

namespace wspace {

auto Station::get_name() const -> std::string_view
{
    return "Atlas Breakpoint";
}

auto Station::get_position() const -> Point<double, 3>
{
    return _position;
}

void Station::set_position(Point<double, 3> new_position)
{
    _position = new_position;
}

} // namespace wspace
