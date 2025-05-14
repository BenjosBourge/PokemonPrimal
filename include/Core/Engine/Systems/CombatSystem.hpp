/*
** Pokemon Primal
** File description:
** PlayerMovementSystem
*/

#pragma once
#include <Engine/Systems/ISystem.hpp>
#include <Engine/Components/Trainer.hpp>
#include <Engine/Components/Player.hpp>

class Combat {
public:
    Combat() {}
    ~Combat() {}

    std::vector<std::shared_ptr<Entity>> _trainers;
};

class CombatSystem : virtual public ISystem {
public:
    CombatSystem();
    ~CombatSystem();

    std::vector<NetworkEvent> update(std::shared_ptr<EntityManager>&, float deltaTime);

private:
    std::vector<Combat> _combats;
};
