#ifndef WSPACE_STATION_HPP_06DAE7F2E5D1436FB0D33D1370873629
#define WSPACE_STATION_HPP_06DAE7F2E5D1436FB0D33D1370873629

#include <wspace/affine_space.hpp>

#include <string_view>

namespace wspace {

class Station
{
public:
    auto get_name() const -> std::string_view;

    auto get_position() const -> Point<double, 3>;
    void set_position(Point<double, 3> new_position);

private:
    Point<double, 3> _position;
};

} // namespace wspace

#endif // WSPACE_STATION_HPP_06DAE7F2E5D1436FB0D33D1370873629
