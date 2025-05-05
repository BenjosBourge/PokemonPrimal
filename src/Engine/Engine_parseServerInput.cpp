/*
** Pokemon Primal
** File description:
** Engine: parseServerInput
*/

#include <Engine/Engine.hpp>

std::vector<NetworkEvent> Engine::processToken(std::string token)
{
    if (token.empty())
        return {};
    if (token.find('_') == std::string::npos)
        return {};
    std::vector<NetworkEvent> events;

    std::string client = token.substr(0, token.find('_'));
    token = token.substr(token.find('_') + 1);

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
        gameObjects->addConnectedEntity(client, newPlayerEntityId);
        std::cout << "New connected Entity: " << client << " with Entity ID: " << newPlayerEntityId << std::endl;
        events.push_back(NetworkEvent(newPlayerEntityId, "Pc_" + client.substr(1), COM_TCP_BROADCAST));
        return events;
    }

    // removing player
    if (command == "RC" && args.size() == 1) {
        std::string playerId = args[0];

        return events;
    }

    // inputs
    if (command == "Up" && args.size() == 1) {
        auto entity = gameObjects->getConnectedEntity(client);
        if (!entity) {
            std::cout << "Entity not found" << std::endl;
            return events;
        }
        entity->getComponent<Input>()._upPressed = args[0] == "P" ? true : false;
    }
    if (command == "Do" && args.size() == 1) {
        auto entity = gameObjects->getConnectedEntity(client);
        if (!entity) {
            std::cout << "Entity not found" << std::endl;
            return events;
        }
        entity->getComponent<Input>()._downPressed = args[0] == "P" ? true : false;
    }
    if (command == "Ri" && args.size() == 1) {
        auto entity = gameObjects->getConnectedEntity(client);
        if (!entity) {
            std::cout << "Entity not found" << std::endl;
            return events;
        }
        entity->getComponent<Input>()._rightPressed = args[0] == "P" ? true : false;
    }
    if (command == "Le" && args.size() == 1) {
        auto entity = gameObjects->getConnectedEntity(client);
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