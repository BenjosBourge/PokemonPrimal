/*
** Pokemon Primal
** File description:
** Engine
*/

#include <Engine/Engine.hpp>

Engine::Engine()
{
    gameObjects = std::make_shared<EntityManager>();
}

Engine::~Engine() { }

void Engine::start()
{
    _entityFactory = EntityFactory();
    _systems.push_back(std::make_shared<MvtSystem>());
    _systems.push_back(std::make_shared<PlayerMovementSystem>());
}

std::string Engine::restart(bool &startGame, int &lastEntityId) 
{
    return "restart";
}

void Engine::clean()
{
    for (auto &entity : gameObjects->entitiesToDestroy) {
        gameObjects->destroyEntity(*entity);
    }
    gameObjects->entitiesToDestroy.clear();
    gameObjects->entitiesDamaged.clear();
}

std::vector<NetworkEvent> Engine::update(float deltaTime)
{
    std::vector<NetworkEvent> output;

    for (auto &system : _systems) {
        std::vector<NetworkEvent> events = system->update(gameObjects, deltaTime);
        if (events.empty())
            continue;
        output.insert(output.end(), events.begin(), events.end());
    }

    /* Check if events are SECURE_BROADCAST, if yes, change client ID */
    for (auto &event : output) {
        if (event.communicationType == COM_SECURE_BROADCAST) {
            std::string tag = gameObjects->getConnectedEntityTag(event.entityId);
            event.clientId = tag[tag.size() - 1] - '0'; //get the n in Pn
        }
    }

    return output;
}
