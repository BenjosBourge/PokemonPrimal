/*
** Pokemon Primal
** File description:
** Position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_
#include <Engine/Components/IComponent.hpp>
#include <iostream>
#include <SFML/System/Vector2.hpp>

enum mapPosition {
    MAP_DEMO_1,
    MAP_DEMO_2,
    MAP_DEMO_3
};

class Position : virtual public IComponent {
public:
    int x;
    int y;
    mapPosition map;

    float speed = 1;
    float timerMove = 0;

    sf::Vector2i direction = {0, 0};

    Position() {
        x = 0;
        y = 0;
        map = MAP_DEMO_1;
    }
    Position(int x, int y, mapPosition map = MAP_DEMO_1, float speed = 1)
        : x(x), y(y), map(map), speed(speed) {}

    ~Position() = default;
};
inline std::ostream& operator<<(std::ostream& out, const Position* pos)
{
    out << "Position: " << pos->x << ", " << pos->y << std::endl;
    return out;
}

#endif /* !POSITION_HPP_ */
