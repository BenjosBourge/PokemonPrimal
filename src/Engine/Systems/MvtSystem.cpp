/*
** Pokemon Primal
** File description:
** MvtSystem
*/

#include "Engine/Systems/MvtSystem.hpp"

MvtSystem::MvtSystem() { }

MvtSystem::~MvtSystem() { }

std::string MvtSystem::update(std::shared_ptr<EntityManager>& entityManager, float deltaTime)
{
    std::string output = "";

    for (auto& [_, entity] : entityManager->getEntities()) {
        if (!entity->hasComponent<Position>())
            continue;
        auto& position = entity->getComponent<Position>();

        if (position.timerMove > 0) {
            position.timerMove -= deltaTime * position.speed;
            continue;
        }
        if (position.direction == sf::Vector2i(0, 0))
            continue;

        position.x += position.direction.x;
        position.y += position.direction.y;
        output += std::to_string(entity->id) + " " +
                  std::to_string(position.x) + " " +
                  std::to_string(position.y) + ":";
    }
    return output;
}

