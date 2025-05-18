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

    if (command == "SpT") {
        std::cout << "Trainer:" << args[0] << std::endl;
        int currentArgs = 1;
        while (currentArgs < args.size()) {
            if (currentArgs + 1 >= args.size())
                break;
            std::cout << "Id: " << args[currentArgs] <<std::endl;
            std::cout << "AllStats: " << args[currentArgs + 1] << std::endl;

            // get every hexadecimal value
            std::string hex = args[currentArgs + 1];

            std::vector<int> values;
            while (hex.size() > 1) {
                std::string hexValue = hex.substr(0, 2);
                std::cout << "Hex: " << hexValue << std::endl;
                std::string value = std::to_string(std::stoi(hexValue, nullptr, 16));
                std::cout << "Value: " << value << std::endl;
                hex = hex.substr(2);
                values.push_back(std::stoi(value));
            }

            if (values.size() != 13) {
                std::cerr << "Error: not enough values" << std::endl;
                return;
            }

            std::cout << "PvMax: " << values[0] << std::endl;
            std::cout << "Pv: " << values[1] << std::endl;
            std::cout << "Attack: " << values[2] << std::endl;
            std::cout << "Defense: " << values[3] << std::endl;
            std::cout << "SpecialAttack: " << values[4] << std::endl;
            std::cout << "SpecialDefense: " << values[5] << std::endl;
            std::cout << "Speed: " << values[6] << std::endl;
            std::cout << "Lvl: " << values[7] << std::endl;
            std::cout << "Exp: " << values[8] << std::endl;
            std::cout << "At1: " << values[9] << std::endl;
            std::cout << "At2: " << values[10] << std::endl;
            std::cout << "At3: " << values[11] << std::endl;
            std::cout << "At4: " << values[12] << std::endl;

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