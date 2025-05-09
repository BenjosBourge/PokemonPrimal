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
    _systems.push_back(std::make_shared<NPCMovementSystem>());
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

    return output;
}

std::shared_ptr<Entity> Engine::createEntity(std::string name)
{
    int id = gameObjects->createEntity(_entityFactory.createEntity(name));
    std::shared_ptr<Entity> newEntity = gameObjects->getEntityById(id);

    return newEntity;
}
