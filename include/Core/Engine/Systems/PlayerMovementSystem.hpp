/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** MvtSystem
*/

#pragma once
#include <Engine/Systems/ISystem.hpp>
#include <Engine/Components/Position.hpp>
#include <Engine/Components/Input.hpp>

class PlayerMovementSystem : virtual public ISystem {
public:
    PlayerMovementSystem();
    ~PlayerMovementSystem();

    std::string update(std::shared_ptr<EntityManager>&, float deltaTime);
};
