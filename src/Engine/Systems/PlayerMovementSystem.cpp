/*
** Pokemon Primal
** File description:
** PlayerMovementSystem
*/

#include "Engine/Systems/PlayerMovementSystem.hpp"

PlayerMovementSystem::PlayerMovementSystem() { }

PlayerMovementSystem::~PlayerMovementSystem() { }

std::string PlayerMovementSystem::update(std::shared_ptr<EntityManager>& entityManager, float deltaTime)
{
    std::string output = "";

    for (auto& [_, entity] : entityManager->getEntities()) {
        if (!entity->hasComponent<Position>() || !entity->hasComponent<Input>())
            continue;
        auto &position = entity->getComponent<Position>();
        auto &input = entity->getComponent<Input>();

        if (input._upPressed)
            position.direction.y -= 1;
        if (input._downPressed)
            position.direction.y += 1;
        if (input._leftPressed)
            position.direction.x -= 1;
        if (input._rightPressed)
            position.direction.x += 1;

        if (!input._upPressed && !input._downPressed)
            position.direction.y = 0;
        if (!input._leftPressed && !input._rightPressed)
            position.direction.x = 0;
    }
    return output;
}

