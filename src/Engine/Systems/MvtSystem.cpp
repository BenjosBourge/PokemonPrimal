/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** MvtSystem
*/

#include "Engine/Systems/MvtSystem.hpp"

MvtSystem::MvtSystem() { }

MvtSystem::~MvtSystem() { }

void MvtSystem::update(std::shared_ptr<EntityManager>& entityManager, float deltaTime)
{
    for (auto& [_, entity] : entityManager->getEntities()) {
        auto& position = entity->getComponent<Position>();

        position.x += 1 * position.speed;
        position.y += 1 * position.speed;

    }
}

