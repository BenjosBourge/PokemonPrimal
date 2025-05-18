/*
** Pokemon Primal
** File description:
** PlayerMovementSystem
*/

#include "Engine/Systems/PlayerMovementSystem.hpp"
#include <Engine/Systems/CombatSystem.hpp>

PlayerMovementSystem::PlayerMovementSystem() { }

PlayerMovementSystem::~PlayerMovementSystem() { }

std::string getHexa(int value)
{
    std::stringstream ss;
    ss << std::hex << value;
    if (ss.str().length() == 1)
        return "0" + ss.str();
    return ss.str();
}

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
            std::shared_ptr<Entity> newEntity = entityManager->newEntity("DemoTrainer");
            entityManager->addConnectedEntity("DT", newEntity->id);
            combatSystem->newCombat({entity}, {newEntity});

            std::string dataPokemon;
            for (auto &pokemon : entity->getComponent<Trainer>()._pokemons) {
                if (pokemon._id == NULL_POKEMON)
                    continue;
                dataPokemon += std::to_string(pokemon._id) + "_";
                dataPokemon += getHexa(pokemon._maxHp) + getHexa(pokemon._currentHp) + getHexa(pokemon._currentAttack)
                    + getHexa(pokemon._currentDefense) + getHexa(pokemon._currentSpeAttack) + getHexa(pokemon._currentSpeDefense)
                    + getHexa(pokemon._currentSpeed) + getHexa(pokemon._level) + getHexa(pokemon._exp);

                dataPokemon += getHexa(pokemon._move1._id) + getHexa(pokemon._move2._id)
                    + getHexa(pokemon._move3._id) + getHexa(pokemon._move4._id);

                dataPokemon += "_";
            }

            output.emplace_back(entity->tag[entity->tag.size() - 1] - '0', "", COM_SET_STATE, CLIENT_BATTLE);
            output.emplace_back(entity->tag[entity->tag.size() - 1] - '0', "Cs_1:", COM_TCP, CLIENT_BATTLE);
            int pos = entity->getComponent<Trainer>()._posInCombat;
            output.emplace_back(entity->tag[entity->tag.size() - 1] - '0', "SpT_" + std::to_string(pos) + "_" + dataPokemon, COM_TCP, CLIENT_BATTLE);
        }
    }
    return output;
}

