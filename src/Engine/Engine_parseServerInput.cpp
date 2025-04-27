/*
** Pokemon Primal
** File description:
** Engine: parseServerInput
*/

#include <Engine/Engine.hpp>

std::vector<NetworkEvent> Engine::processToken(const std::string &token)
{
    std::vector<NetworkEvent> events;
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
        int newPlayerEntityId = gameObjects->createEntity(_entityFactory.createEntity("Player"));
        gameObjects->addConnectedEntity("P" + args[0], newPlayerEntityId);
        std::cout << "New connected Entity: P" << args[0] << " with Entity ID: " << newPlayerEntityId << std::endl;
        events.push_back(NetworkEvent(newPlayerEntityId, "Pc_" + args[0], COM_TCP_BROADCAST));
    }

    // inputs
    if (command == "Up" && args.size() == 2) {
        std::string playerId = args[1];

        auto entity = gameObjects->getConnectedEntity(playerId);
        if (!entity) {
            std::cout << "Entity not found" << std::endl;
            return events;
        }
        entity->getComponent<Input>()._upPressed = args[0] == "P" ? true : false;
    }
    if (command == "Do" && args.size() == 2) {
        std::string playerId = args[1];

        auto entity = gameObjects->getConnectedEntity(playerId);
        if (!entity) {
            std::cout << "Entity not found" << std::endl;
            return events;
        }
        entity->getComponent<Input>()._downPressed = args[0] == "P" ? true : false;
    }
    if (command == "Ri" && args.size() == 2) {
        std::string playerId = args[1];

        auto entity = gameObjects->getConnectedEntity(playerId);
        if (!entity) {
            std::cout << "Entity not found" << std::endl;
            return events;
        }
        entity->getComponent<Input>()._rightPressed = args[0] == "P" ? true : false;
    }
    if (command == "Le" && args.size() == 2) {
        std::string playerId = args[1];

        auto entity = gameObjects->getConnectedEntity(playerId);
        if (!entity) {
            std::cout << "Entity not found" << std::endl;
            return events;
        }
        entity->getComponent<Input>()._leftPressed = args[0] == "P" ? true : false;
    }
    return events;
}

std::vector<NetworkEvent> Engine::parseServerInput(const std::string &input)
{
    std::vector<NetworkEvent> events;
    std::stringstream ss(input);
    std::string tmp;

    while (std::getline(ss, tmp, ':')) {
        std::vector<NetworkEvent> tmpEvents = processToken(tmp);
        if (tmpEvents.empty())
            continue;
        events.insert(events.end(), tmpEvents.begin(), tmpEvents.end());
    }
    return events;
}