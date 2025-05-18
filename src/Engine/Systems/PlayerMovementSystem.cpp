/*
** Pokemon Primal
** File description:
** PlayerMovementSystem
*/

#include "Engine/Systems/PlayerMovementSystem.hpp"
#include <Engine/Systems/CombatSystem.hpp>

PlayerMovementSystem::PlayerMovementSystem() { }

PlayerMovementSystem::~PlayerMovementSystem() { }

std::vector<NetworkEvent> PlayerMovementSystem::update(std::shared_ptr<EntityManager>& entityManager, float deltaTime)
{
    std::vector<NetworkEvent> output;

    for (auto& [_, entity] : entityManager->getEntities()) {
        if (!entity->hasComponent<Position>() || !entity->hasComponent<Input>() || !entity->hasComponent<Player>())
            continue;
        auto &position = entity->getComponent<Position>();
        auto &input = entity->getComponent<Input>();
        auto &player = entity->getComponent<Player>();

        if (player._playerState != CLIENT_OVERWORLD)
            continue;

        if (input._upPressed)
            position.direction.y = -1;
        if (input._downPressed)
            position.direction.y = 1;
        if (input._leftPressed)
            position.direction.x = -1;
        if (input._rightPressed)
            position.direction.x = 1;

        if (!input._upPressed && !input._downPressed)
            position.direction.y = 0;
        if (!input._leftPressed && !input._rightPressed)
            position.direction.x = 0;

        if (input._spacePressed) {
            std::cout << "Launch a Battle" << std::endl;
            player._playerState = CLIENT_BATTLE;

            std::shared_ptr<CombatSystem> combatSystem = std::dynamic_pointer_cast<CombatSystem>(_systems["CombatSystem"]);
            entityManager->_entityFactory.createEntity("DemoTrainer");
            entityManager->addConnectedEntity("DT", entity->id);
            std::shared_ptr<Entity> newEntity = entityManager->newEntity("DemoTrainer");
            combatSystem->newCombat({entity}, {newEntity});

            output.emplace_back(entity->tag[entity->tag.size() - 1] - '0', "", COM_SET_STATE, CLIENT_BATTLE);
            output.emplace_back(entity->tag[entity->tag.size() - 1] - '0', "Cs_1:", COM_TCP, CLIENT_BATTLE);
        }
    }
    return output;
}

