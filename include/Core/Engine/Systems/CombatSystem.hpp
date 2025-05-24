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

    std::vector<NetworkEvent> turn();
    std::shared_ptr<Entity> getTrainerFromPos(int pos);

    std::vector<std::shared_ptr<Entity>> _trainers1;
    std::vector<std::shared_ptr<Entity>> _trainers2;
};

class CombatSystem : virtual public ISystem {
public:
    CombatSystem();
    ~CombatSystem();

    std::vector<NetworkEvent> update(std::shared_ptr<EntityManager>&, float deltaTime);
    void newCombat(std::vector<std::shared_ptr<Entity>> trainers1, std::vector<std::shared_ptr<Entity>> trainers2);

private:
    std::vector<Combat> _combats;
};
