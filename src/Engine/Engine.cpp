/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
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
}

std::string Engine::restart(bool &startGame, int &lastEntityId) 
{
    return "restart";
}

int Engine::addPlayer()
{
    int id = gameObjects->createEntity(_entityFactory.createEntity("Player"));
    if (gameObjects->hasEntity(id)) {
      
        gameObjects->getEntityById(id)->getComponent<Position>().y = 60 * id;
    }
    return id;
}

void Engine::clean()
{
    for (auto &entity : gameObjects->entitiesToDestroy) {
        gameObjects->destroyEntity(*entity);
    }
    gameObjects->entitiesToDestroy.clear();
    gameObjects->entitiesDamaged.clear();
}

void Engine::update(float deltaTime)
{
    std::cout << "Updating engine... with deltaTime: " << deltaTime << std::endl;
    for (auto &system : _systems) {
        system->update(gameObjects, deltaTime);
    }
}
