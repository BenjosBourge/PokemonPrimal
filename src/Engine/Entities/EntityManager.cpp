/*
** Pokemon Primal
** File description:
** EntityManager
*/

#include "Engine/Entities/EntityManager.hpp"

EntityManager::EntityManager() { }

EntityManager::~EntityManager() { }

int EntityManager::createEntity(Entity& entity)
{
    nbEntities++;
    entity.id = nbEntities;
    _entities[entity.id] = std::make_shared<Entity>(entity);
    return entity.id;
}

void EntityManager::destroyEntity(Entity& entity)
{
    _entities.erase(entity.id);
}

void EntityManager::printEntities()
{
    for (auto& entity : _entities) {
        std::cout << "Entity " << entity.first << std::endl;
    }
}

std::shared_ptr<Entity> EntityManager::getEntityById(int id)
{
    return _entities[id];
}

bool EntityManager::hasEntity(int id)
{
    auto it = _entities.find(id);
    return it != _entities.end();
}

std::map<int, std::shared_ptr<Entity>> EntityManager::getEntities()
{
    return _entities;
}

void EntityManager::destroyEntityById(int id)
{
    if (_entities.find(id) == _entities.end()) {
        std::cout << "Entity " << id << " not found can't destroy it" << std::endl;
        return;
    }
    entitiesToDestroy.push_back(_entities[id]);
    _entities.erase(id);
}

void EntityManager::addConnectedEntity(std::string name, int id)
{
    _entities[id]->tag = name;
    _connectedEntities[name] = id;
}

std::shared_ptr<Entity> EntityManager::getConnectedEntity(std::string name)
{
    if (_connectedEntities.find(name) == _connectedEntities.end()) {
        std::cout << "Entity " << name << " not found" << std::endl;

        for (auto& entity : _connectedEntities) {
            std::cout << "Entity " << entity.first << " with ID: " << entity.second << std::endl;
        }
        return nullptr;
    }
    return getEntityById(_connectedEntities[name]);
}

std::string EntityManager::getConnectedEntityTag(int id)
{
    for (auto& entity : _connectedEntities) {
        if (entity.second == id)
            return entity.first;
    }
    return "";
}