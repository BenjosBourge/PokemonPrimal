/*
** Pokemon Primal
** File description:
** CombatSystem
*/

#include <utility>

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

            std::vector<NetworkEvent> no = combat.turn();
            for (auto &n : no)
                output.push_back(n);

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
    combat._trainers1 = std::move(trainers1);
    int pos = 0;
    for (auto& trainer : combat._trainers1) {
        auto &trainerComponent = trainer->getComponent<Trainer>();
        trainerComponent._posInCombat = pos;
        trainerComponent._target = 1;
        pos++;
    }
    combat._trainers2 = std::move(trainers2);
    for (auto& trainer : combat._trainers2) {
        auto &trainerComponent = trainer->getComponent<Trainer>();
        trainerComponent._posInCombat = pos;
        trainerComponent._target = 0;
        pos++;
    }
    _combats.push_back(combat);
}


// Combat methods

std::vector<NetworkEvent> Combat::turn()
{
    std::vector<NetworkEvent> output;

    std::vector<PokemonMove> moves;
    for (auto& trainer : _trainers1) {
        auto &trainerComponent = trainer->getComponent<Trainer>();
        PokemonMove move;
        move = trainerComponent._pokemons[trainerComponent._posInCombat]->_moves[trainerComponent._attackSelected];
        move._user = trainerComponent._posInCombat;
        move._target = trainerComponent._target;
        moves.emplace_back(move);
    }
    for (auto& trainer : _trainers2) {
        auto &trainerComponent = trainer->getComponent<Trainer>();
        PokemonMove move;
        move = trainerComponent._pokemons[trainerComponent._posInCombat]->_moves[trainerComponent._attackSelected];
        move._user = trainerComponent._posInCombat;
        move._target = trainerComponent._target;
        moves.emplace_back(move);
    }

    //Get the moves in order
    std::vector<PokemonMove> sortedMoves;
    std::vector<int> indexUsed;
    int size = moves.size();
    for (int i = 0; i < size; i++) {
        int maxIndex = 0;
        while (std::find(indexUsed.begin(), indexUsed.end(), maxIndex) != indexUsed.end())
            maxIndex++;

        auto trainer = getTrainerFromPos(moves[maxIndex]._user)->getComponent<Trainer>();
        auto &maxPokemon = trainer._pokemons[0];

        for (int j = 1; j < moves.size(); j++) {
            if (std::find(indexUsed.begin(), indexUsed.end(), j) != indexUsed.end())
                continue;

            auto trainer2 = getTrainerFromPos(moves[j]._user)->getComponent<Trainer>();
            auto &pokemon2 = trainer2._pokemons[0];
            if (pokemon2->_currentSpeed > maxPokemon->_currentSpeed) {
                maxIndex = j;
                maxPokemon = pokemon2;
            }
        }
        sortedMoves.push_back(moves[maxIndex]);
        indexUsed.push_back(maxIndex);
    }

    //Execute the moves
    for (auto& move : sortedMoves) {
        auto trainer = getTrainerFromPos(move._user)->getComponent<Trainer>();
        auto pokemon = trainer._pokemons[0];
        auto targetTrainer = getTrainerFromPos(move._target)->getComponent<Trainer>();
        auto targetPokemon = targetTrainer._pokemons[0];

        if (move._power > 0) {
            int damage = targetPokemon->takeDamage(*pokemon, move);
            std::string event = "At_" + std::to_string(move._user) + "_" + std::to_string(move._target) + "_" + std::to_string(damage);
            NetworkEvent networkEvent(-1, event, COM_TCP_BROADCAST, CLIENT_BATTLE);
            output.push_back(networkEvent);
        }
    }
    return output;
}

std::shared_ptr<Entity> Combat::getTrainerFromPos(int pos)
{
    if (pos < _trainers1.size())
        return _trainers1[pos];
    pos -= _trainers1.size();
    if (pos < _trainers2.size())
        return _trainers2[pos];
    return nullptr;
}
