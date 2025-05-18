/*
** Pokemon Primal
** File description:
** PlayerMovementSystem
*/

#pragma once
#include <Engine/Systems/ISystem.hpp>
#include <Engine/Components/Position.hpp>
#include <Engine/Components/Input.hpp>
#include <Engine/Components/Player.hpp>

class PlayerMovementSystem : virtual public ISystem {
public:
    PlayerMovementSystem();
    ~PlayerMovementSystem();

    std::vector<NetworkEvent> update(std::shared_ptr<EntityManager>&, float deltaTime);
};
