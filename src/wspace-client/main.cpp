
#include <wspace/asteroid.hpp>
#include <wspace/player.hpp>
#include <wspace/station.hpp>

#include <iostream>

int main()
{
    auto asteroid = wspace::Asteroid{};

    auto station = wspace::Station{};
    station.set_position({1., 2., 3.});
    std::cout << "Station: " << station.get_name() << std::endl;
    std::cout << "  " << station.get_position() << std::endl;

    auto player = wspace::Player{};
    player.set_position({});
    player.set_target_position(station.get_position());
    player.set_speed(1);
    std::cout << "Player: " << player.get_name() << std::endl;
    std::cout << "  " << player.get_position() << std::endl;
    std::cout << "  " << player.get_target_position() << std::endl;

    for (std::size_t step = 0; step < 10; ++step)
    {
        player.update(0.01);
        std::cout << player.get_position() << std::endl;
    }
}
