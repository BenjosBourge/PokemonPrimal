/*
** Pokemon Primal
** File description:
** Engine: parseServerInput
*/

#include <Engine/Engine.hpp>

void Engine::processToken(const std::string &token)
{
    std::string command = token.substr(0, token.find('_'));
    std::vector<std::string> args;

    // getting arguments to command
    std::string arg = token.substr(token.find('_') + 1);
    std::stringstream ss(arg);
    std::string tmp;
    while (std::getline(ss, tmp, '_'))
        args.push_back(tmp);

    // creating new player
    if (command == "NC" && args.size() == 1) {
        int newPlayerId = gameObjects->createEntity(_entityFactory.createEntity("Player"));
        gameObjects->addConnectedEntity("P" + args[0], newPlayerId);
        std::cout << "New connected Entity: " << args[0] << " with ID: " << newPlayerId << std::endl;
    }

    // inputs
    if (command == "Up" && args.size() == 2) {
        std::string playerId = args[1];

        auto entity = gameObjects->getConnectedEntity(playerId);
        if (!entity) {
            std::cout << "Entity not found" << std::endl;
            return;
        }
        entity->getComponent<Input>()._upPressed = args[0] == "P" ? true : false;
    }
    if (command == "Do" && args.size() == 2) {
        std::string playerId = args[1];

        auto entity = gameObjects->getConnectedEntity(playerId);
        if (!entity) {
            std::cout << "Entity not found" << std::endl;
            return;
        }
        entity->getComponent<Input>()._downPressed = args[0] == "P" ? true : false;
    }
    if (command == "Ri" && args.size() == 2) {
        std::string playerId = args[1];

        auto entity = gameObjects->getConnectedEntity(playerId);
        if (!entity) {
            std::cout << "Entity not found" << std::endl;
            return;
        }
        entity->getComponent<Input>()._rightPressed = args[0] == "P" ? true : false;
    }
    if (command == "Le" && args.size() == 2) {
        std::string playerId = args[1];

        auto entity = gameObjects->getConnectedEntity(playerId);
        if (!entity) {
            std::cout << "Entity not found" << std::endl;
            return;
        }
        entity->getComponent<Input>()._leftPressed = args[0] == "P" ? true : false;
    }
}

void Engine::parseServerInput(const std::string &input)
{
    std::stringstream ss(input);
    std::string tmp;

    while (std::getline(ss, tmp, ':'))
        processToken(tmp);
}