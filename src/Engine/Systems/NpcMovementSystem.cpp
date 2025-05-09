/*
** Pokemon Primal
** File description:
** PlayerMovementSystem
*/

#include "Engine/Systems/NpcMovementSystem.hpp"

NPCMovementSystem::NPCMovementSystem() { }

NPCMovementSystem::~NPCMovementSystem() { }

std::vector<NetworkEvent> NPCMovementSystem::update(std::shared_ptr<EntityManager>& entityManager, float deltaTime)
{
    for (auto& [_, entity] : entityManager->getEntities()) {
        if (!entity->hasComponent<Position>() || !entity->hasComponent<NPC>())
            continue;
        auto &position = entity->getComponent<Position>();
        auto &npc = entity->getComponent<NPC>();

        position.direction = npc.pattern->move({position.x, position.y});
    }
    return {};
}

