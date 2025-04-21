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

std::string Engine::update(float deltaTime)
{
    std::string output = "";

    for (auto &system : _systems) {
        output += system->update(gameObjects, deltaTime);
    }
    return output;
}
