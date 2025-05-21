/*
** Pokemon Primal
** File description:
** Game: parseClientInput
*/

#include <SFML/Graphics.hpp>
#include <Game.hpp>
#include <Scene/Overworld.hpp>
#include <Objects/Character.hpp>

void Game::processToken(const std::string &token)
{
    std::string command = token.substr(0, token.find('_'));
    std::vector<std::string> args;

    // getting arguments to command
    std::string arg = token.substr(token.find('_') + 1);
    std::stringstream ss(arg);
    std::string tmp;
    while (std::getline(ss, tmp, '_'))
        args.push_back(tmp);

    std::cout << "Command: " << command << " Args: " << args.size() << std::endl;
    if (command == "Pc" && args.size() == 1) {
        auto &scene = _scenes[GameState::STATE_OVERWORLD];
        if (scene) {
            std::shared_ptr<Overworld> overworldScene = std::dynamic_pointer_cast<Overworld>(scene);
            overworldScene->addCharacter(args[0]);
        }
    }

    if (command == "Pd" && args.size() == 1) {
        auto &scene = _scenes[GameState::STATE_OVERWORLD];
        if (scene) {
            std::shared_ptr<Overworld> overworldScene = std::dynamic_pointer_cast<Overworld>(scene);
            overworldScene->removeCharacter(args[0]);
        }
    }

    if (command == "Pp" && args.size() == 4) {
        auto &scene = _scenes[GameState::STATE_OVERWORLD];
        if (scene) {
            std::shared_ptr<Overworld> overworldScene = std::dynamic_pointer_cast<Overworld>(scene);
            std::shared_ptr<Character> player = overworldScene->getCharacter(args[0]);

            if (player) {
                if (args[1] == "0")
                    player->moveTo(std::stoi(args[2]), std::stoi(args[3]));
                else
                    player->setPosition(std::stoi(args[2]), std::stoi(args[3]));
            } else {
                std::cerr << "Player " << args[0] << " not found" << std::endl;
            }
        }
    }

    if (command == "Pir" && args.size() == 1) {
        auto &scene = _scenes[GameState::STATE_OVERWORLD];
        if (scene) {
            std::shared_ptr<Overworld> overworldScene = std::dynamic_pointer_cast<Overworld>(scene);
            std::shared_ptr<Character> player = overworldScene->getCharacter(args[0]);

            if (player) {
                player->setMotion(false);
            } else {
                std::cerr << "Player " << args[0] << " not found" << std::endl;
            }
        }
    }

    if (command == "Cs" && args.size() == 1) {
        int id = std::stoi(args[0]);
        if (id == 0)
            _currentState = GameState::STATE_OVERWORLD;
        else if (id == 1)
            _currentState = GameState::STATE_BATTLE;
    }

    if (command == "Cl" && args.size() == 2) {
        auto &scene = _scenes[GameState::STATE_BATTLE];
        if (scene) {
            std::shared_ptr<Battle> battleScene = std::dynamic_pointer_cast<Battle>(scene);

            int nbTeam1 = std::stoi(args[0]);
            int nbTeam2 = std::stoi(args[1]);

            battleScene->_nbTeam1 = nbTeam1;
            battleScene->_nbTeam2 = nbTeam2;

            for (int i = 0; i < nbTeam1; i++)
                battleScene->_trainers[i]->_inBattle = true;

            for (int i = 0; i < nbTeam2; i++)
                battleScene->_trainers[i + 4]->_inBattle = true;
        }
    }

    if (command == "SpT") {
        auto &scene = _scenes[GameState::STATE_BATTLE];
        std::shared_ptr<Battle> battleScene = std::dynamic_pointer_cast<Battle>(scene);

        try {
            int id = std::stoi(args[0]);
            if (id < 0 || id >= battleScene->_trainers.size()) {
                std::cerr << "Error: Trainer ID out of range" << std::endl;
                return;
            }
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error: Invalid trainer ID" << std::endl;
            return;
        }

        int trainerPos = std::stoi(args[0]);
        if (trainerPos < 0 || trainerPos >= battleScene->_trainers.size()) {
            std::cerr << "Error: Trainer ID out of range" << std::endl;
            return;
        }
        if (trainerPos >= battleScene->_nbTeam1) {
            trainerPos = trainerPos % battleScene->_nbTeam1;
            trainerPos += 4;
        }
        auto &trainer = battleScene->_trainers[trainerPos];

        int currentArgs = 1;
        int currentPokemon = 0;
        while (currentArgs < args.size()) {
            if (currentArgs + 1 >= args.size())
                break;

            std::string hex = args[currentArgs + 1];
            std::vector<int> values;
            while (hex.size() > 1) {
                std::string hexValue = hex.substr(0, 2);
                std::string value = std::to_string(std::stoi(hexValue, nullptr, 16));
                hex = hex.substr(2);
                values.push_back(std::stoi(value));
            }

            if (values.size() != 13) {
                std::cerr << "Error: not enough values" << std::endl;
                return;
            }
            try {
                std::stoi(args[currentArgs]);
            } catch (const std::invalid_argument &e) {
                std::cerr << "Error: Invalid Pokemon ID" << std::endl;
                return;
            }

            std::cout << static_cast<PokemonId>(std::stoi(args[currentArgs])) << std::endl;
            trainer->_pokemons[currentPokemon]._id = static_cast<PokemonId>(std::stoi(args[currentArgs]));
            //PvMaxPvAtkDefAtkSpeDefSpeVitLvlExpAt1IdAt2IdAt3IdAt4Id
            trainer->_pokemons[currentPokemon]._maxHp = values[0];
            trainer->_pokemons[currentPokemon]._currentHp = values[1];
            trainer->_pokemons[currentPokemon]._currentAttack = values[2];
            trainer->_pokemons[currentPokemon]._currentDefense = values[3];
            trainer->_pokemons[currentPokemon]._currentSpeAttack = values[4];
            trainer->_pokemons[currentPokemon]._currentSpeDefense = values[5];
            trainer->_pokemons[currentPokemon]._currentSpeed = values[6];
            trainer->_pokemons[currentPokemon]._level = values[7];
            trainer->_pokemons[currentPokemon]._exp = values[8];
            trainer->_pokemons[currentPokemon]._moves[0] = pokemonMoves[static_cast<PokemonMoveId>(values[9])];
            trainer->_pokemons[currentPokemon]._moves[1] = pokemonMoves[static_cast<PokemonMoveId>(values[10])];
            trainer->_pokemons[currentPokemon]._moves[2] = pokemonMoves[static_cast<PokemonMoveId>(values[11])];
            trainer->_pokemons[currentPokemon]._moves[3] = pokemonMoves[static_cast<PokemonMoveId>(values[12])];

            std::cout << "Pokemon Moves: " << trainer->_pokemons[currentPokemon]._moves[0]._name << " "
                      << trainer->_pokemons[currentPokemon]._moves[1]._name << " "
                      << trainer->_pokemons[currentPokemon]._moves[2]._name << " "
                      << trainer->_pokemons[currentPokemon]._moves[3]._name << std::endl;

            currentPokemon++;

            if (currentPokemon >= 6) {
                std::cerr << "Error: too many pokemons" << std::endl;
                return;
            }
            currentArgs += 2;
        }
    }
}

void Game::parseClientInput(const std::string &input)
{
    if (input.empty())
        return;
    std::stringstream ss(input);
    std::string tmp;

    while (std::getline(ss, tmp, ':'))
        processToken(tmp);
}