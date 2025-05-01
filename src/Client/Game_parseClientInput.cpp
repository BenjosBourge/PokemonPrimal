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
            overworldScene->addCharacter("Player"+args[0]);
        }
    }

    if (command == "Pp" && args.size() == 3) {
        auto &scene = _scenes[GameState::STATE_OVERWORLD];
        if (scene) {
            std::shared_ptr<Overworld> overworldScene = std::dynamic_pointer_cast<Overworld>(scene);
            std::shared_ptr<Character> player = overworldScene->getCharacter("Player" + args[0]);

            if (player) {
                player->moveTo(std::stoi(args[1]), std::stoi(args[2]));
            } else {
                std::cerr << "Player " << args[0] << " not found" << std::endl;
            }
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