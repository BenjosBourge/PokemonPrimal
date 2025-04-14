/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
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
