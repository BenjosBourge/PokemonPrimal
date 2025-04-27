/*
** Pokemon Primal
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_
#include <Engine/Entities/Entity.hpp>
#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

class ISystem;

class EntityManager {
private:
    std::map<int, std::shared_ptr<Entity>> _entities;
    int nbEntities = 0;

public:
    EntityManager();
    ~EntityManager();

    int createEntity(Entity&);
    void destroyEntity(Entity&);

    void destroyEntityById(int id);

    void printEntities();

    std::shared_ptr<Entity> getEntityById(int id);
    bool hasEntity(int id);
    std::map<int, std::shared_ptr<Entity>> getEntities();

    std::vector<std::shared_ptr<Entity>> entitiesToDestroy;
    std::vector<std::shared_ptr<Entity>> entitiesDamaged;

    /* Each entity and their online tag */
    std::unordered_map<std::string, int> _connectedEntities;
    void addConnectedEntity(std::string name, int id);
    std::shared_ptr<Entity> getConnectedEntity(std::string name);
    std::string getConnectedEntityTag(int id);
};
#endif
