/*
** Pokemon Primal
** File description:
** MvtSystem
*/

#include "Engine/Systems/MvtSystem.hpp"

MvtSystem::MvtSystem() { }

MvtSystem::~MvtSystem() { }

std::vector<NetworkEvent> MvtSystem::update(std::shared_ptr<EntityManager>& entityManager, float deltaTime)
{
    std::vector<NetworkEvent> events;

    for (auto& [_, entity] : entityManager->getEntities()) {
        if (!entity->hasComponent<Position>())
            continue;
        auto& position = entity->getComponent<Position>();

        if (position.timerMove > 0) {
            position.timerMove -= deltaTime * position.speed;
            continue;
        }
        if (position.direction == sf::Vector2i(0, 0)) {
            if (position.inMotion) {
                position.inMotion = false;

                std::string eventType = "Pir_" + entity->tag + ":";
                events.emplace_back(-1, eventType, COM_TCP_BROADCAST);
            }
            continue;
        }

        position.x += position.direction.x;
        if (position.direction.x == 0)
            position.y += position.direction.y;
        position.timerMove = 0.4f;

        // send message to clients for object position
        std::string eventType = "Pp_" + entity->tag + "_0_" +
                          std::to_string(position.x) + "_" +
                          std::to_string(position.y) + ":";
        if (entity->tag[0] == 'P')
            events.emplace_back(entity->tag[entity->tag.size() - 1] - '0', eventType, COM_TCP_BROADCAST);
        else
            events.emplace_back(-1, eventType, COM_TCP_BROADCAST);
        position.inMotion = true;
    }
    return events;
}

