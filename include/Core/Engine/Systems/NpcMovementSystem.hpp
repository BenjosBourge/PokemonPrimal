/*
** Pokemon Primal
** File description:
** PlayerMovementSystem
*/

#pragma once
#include <Engine/Systems/ISystem.hpp>
#include <Engine/Components/Position.hpp>
#include <Engine/Components/NPC.hpp>

class NPCMovementSystem : virtual public ISystem {
public:
    NPCMovementSystem();
    ~NPCMovementSystem();

    std::vector<NetworkEvent> update(std::shared_ptr<EntityManager>&, float deltaTime);
};
