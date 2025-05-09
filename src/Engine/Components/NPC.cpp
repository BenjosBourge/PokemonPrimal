/*
** Pokemon Primal
** File description:
** Entity
*/

#include <Engine/Components/NPC.hpp>

sf::Vector2i StaticPattern::move(sf::Vector2i pos)
{
    std::cout << "Moving in a static pattern" << std::endl;
    return {0, 0};
}

sf::Vector2i LinePattern::move(sf::Vector2i pos)
{
    sf::Vector2i target = a;
    if (index == 0)
        target = a;
    else if (index == 1)
        target = b;

    if (pos.x == target.x && pos.y == target.y) {
        index++;
        if (index > 1)
            index = 0;
        return {0, 0};
    }
    if (pos.x < target.x)
        return {1, 0};
    if (pos.x > target.x)
        return {-1, 0};
    if (pos.y < target.y)
        return {0, 1};
    if (pos.y > target.y)
        return {0, -1};

    return {0, 0};
}

sf::Vector2i SquarePattern::move(sf::Vector2i pos)
{
    sf::Vector2i target = a;
    if (index == 0)
        target = a;
    else if (index == 1)
        target = b;
    else if (index == 2)
        target = c;
    else if (index == 3)
        target = d;

    if (pos.x == target.x && pos.y == target.y) {
        index++;
        if (index > 3)
            index = 0;
        return {0, 0};
    }
    if (pos.x < target.x)
        return {1, 0};
    if (pos.x > target.x)
        return {-1, 0};
    if (pos.y < target.y)
        return {0, 1};
    if (pos.y > target.y)
        return {0, -1};

    return {0, 0};
}

sf::Vector2i RoamingPattern::move(sf::Vector2i pos)
{
    if (pos.x == target.x && pos.y == target.y) {
        target.x = rand() % (b.x - a.x + 1) + a.x;
        target.y = rand() % (b.y - a.y + 1) + a.y;
        return {0, 0};
    }
    if (pos.x < target.x)
        return {1, 0};
    if (pos.x > target.x)
        return {-1, 0};
    if (pos.y < target.y)
        return {0, 1};
    if (pos.y > target.y)
        return {0, -1};

    return {0, 0};
}
