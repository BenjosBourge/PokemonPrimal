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
    int clientId = client[1] - '0'; //get the n in Pn
    token = token.substr(token.find('_') + 1);

    std::string command = token.substr(0, token.find('_'));
    std::vector<std::string> args;

    // getting arguments to command
    std::string arg = token.substr(token.find('_') + 1);
    std::stringstream ss(arg);
    std::string tmp;
    while (std::getline(ss, tmp, '_'))
        args.push_back(tmp);

    if (command == "UDP" && args.size() == 1) {
        try {
            int udpPort = std::stoi(args[0]);

            events.emplace_back(clientId, std::to_string(udpPort), COM_SET_UDP);
            std::cout << "UDP port network event: " << udpPort << std::endl;
        }
        catch (const std::invalid_argument &e) {
            std::cerr << "Invalid UDP port: " << args[0] << std::endl;
        }
        return events;
    }

    // creating new player
    if (command == "NC") {
        int newPlayerEntityId = gameObjects->createEntity(_entityFactory.createEntity("Player"));
        gameObjects->addConnectedEntity(client, newPlayerEntityId);
        std::cout << "New connected Entity: " << client << " with Entity ID: " << newPlayerEntityId << std::endl;
        events.push_back(NetworkEvent(clientId, "Pc_" + client, COM_TCP_BROADCAST));

        for (auto &entity : gameObjects->_connectedEntities) {
            if (entity.first == client)
                continue;
            events.push_back(NetworkEvent(clientId, "Pc_" + entity.first, COM_TCP));
            std::shared_ptr<Entity> newEntity = gameObjects->getConnectedEntity(entity.first);
            std::string eventType = "Pp_" + entity.first + "_1_" +
                                    std::to_string(newEntity->getComponent<Position>().x) + "_" +
                                    std::to_string(newEntity->getComponent<Position>().y) + ":";
            events.push_back(NetworkEvent(clientId, eventType, COM_TCP));
            events.push_back(NetworkEvent(clientId, "Pir_" + entity.first, COM_TCP));
        }
        return events;
    }

    // removing player
    if (command == "RC") {
        int entityId = gameObjects->getConnectedEntity(client)->id;

        gameObjects->removeConnectedEntity(client);
        std::cout << "Disconnected Entity: " << client << " with Entity ID: " << entityId << std::endl;
        events.push_back(NetworkEvent(clientId, "Pd_" + client, COM_TCP_BROADCAST));
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