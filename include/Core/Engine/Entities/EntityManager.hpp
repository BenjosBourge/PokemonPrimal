/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_
#include <Engine/Components/Position.hpp>
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
};
#endif
