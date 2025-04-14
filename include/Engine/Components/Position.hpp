/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** Position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_
#include <Engine/Components/IComponent.hpp>

class Position : virtual public IComponent {
public:
    float x;
    float y;
    float z;

    float speed = 1;

    Position(float x, float y, float z, float speed)
        : x(x)
        , y(y)
        , z(z)
        , speed(speed) {};

    ~Position() = default;
};
inline std::ostream& operator<<(std::ostream& out, const Position* pos)
{
    out << "Position: " << pos->x << ", " << pos->y << ", " << pos->z
        << std::endl;
    return out;
}

#endif /* !POSITION_HPP_ */
