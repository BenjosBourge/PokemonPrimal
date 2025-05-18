/*
** Pokemon Primal
** File description:
** CombatSystem
*/

#include "Engine/Systems/CombatSystem.hpp"

CombatSystem::CombatSystem() { }

CombatSystem::~CombatSystem() { }

std::vector<NetworkEvent> CombatSystem::update(std::shared_ptr<EntityManager>& entityManager, float deltaTime)
{
    std::vector<NetworkEvent> output;

    for (auto& [_, entity] : entityManager->getEntities()) {
        if (!entity->hasComponent<Trainer>())
            continue;
        auto &trainer = entity->getComponent<Trainer>();

        if (!entity->hasComponent<Player>()) {
            if (trainer._attackSelected == -1) {
                trainer._attackSelected = 0;
            }
        }
    }

    for (auto& combat : _combats) {
        bool allReady = true;
        for (auto& trainer : combat._trainers1) {
            auto &trainerComponent = trainer->getComponent<Trainer>();
            if (trainerComponent._attackSelected == -1) {
                allReady = false;
                break;
            }
        }
        for (auto& trainer : combat._trainers2) {
            auto &trainerComponent = trainer->getComponent<Trainer>();
            if (trainerComponent._attackSelected == -1) {
                allReady = false;
                break;
            }
        }

        if (allReady) {
            std::cout << "All trainers are ready" << std::endl;

            for (auto& trainer : combat._trainers1) {
                auto &trainerComponent = trainer->getComponent<Trainer>();
                trainerComponent._attackSelected = -1;
            }
            for (auto& trainer : combat._trainers2) {
                auto &trainerComponent = trainer->getComponent<Trainer>();
                trainerComponent._attackSelected = -1;
            }
        }
    }

    return output;
}

void CombatSystem::newCombat(std::vector<std::shared_ptr<Entity>> trainers1, std::vector<std::shared_ptr<Entity>> trainers2)
{
    Combat combat;
    combat._trainers1 = trainers1;
    combat._trainers2 = trainers2;
    _combats.push_back(combat);
}

