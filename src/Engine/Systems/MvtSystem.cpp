/*
** Pokemon Primal
** File description:
** MvtSystem
*/

#include "Engine/Systems/MvtSystem.hpp"
#include <Maps/MapManager.hpp>

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
                events.emplace_back(-1, eventType, COM_TCP_BROADCAST, CLIENT_OVERWORLD);
            }
            continue;
        }

        int nx = position.x + position.direction.x;
        int ny = position.y;
        if (position.direction.x == 0)
            ny = position.y + position.direction.y;

        if (nx < 0 || nx >= mapManager._maps[position.map]._map[0].size() ||
            ny < 0 || ny >= mapManager._maps[position.map]._map.size()) {
            continue;
        }
        if (!mapManager._maps[position.map]._map[ny][nx]._obstacle) {
            position.x = nx;
            position.y = ny;
            position.timerMove = 0.4f;

            // send message to clients for object position
            std::string eventType = "Pp_" + entity->tag + "_0_" +
                                    std::to_string(position.x) + "_" +
                                    std::to_string(position.y) + ":";
            if (entity->tag[0] == 'P')
                events.emplace_back(entity->tag[entity->tag.size() - 1] - '0', eventType, COM_TCP_BROADCAST, CLIENT_OVERWORLD);
            else
                events.emplace_back(-1, eventType, COM_BROADCAST, CLIENT_OVERWORLD);
            position.inMotion = true;
        }
    }
    return events;
}

