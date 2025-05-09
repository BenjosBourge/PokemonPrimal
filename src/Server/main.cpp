/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-rtype-erwann.laplante
** File description:
** main.cpp
*/

#include <Engine/Engine.hpp>
#include <Server.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Network.hpp>

std::shared_ptr<Entity> createNPC(std::unique_ptr<Engine> &engine, int x, int y, std::string name)
{
    std::shared_ptr<Entity> npc = engine->createEntity("NPC");
    auto &npcComponent = npc->getComponent<NPC>();
    auto &positionComponent = npc->getComponent<Position>();

    positionComponent.x = x;
    positionComponent.y = y;
    engine->gameObjects->addConnectedEntity(name, npc->id);
    npcComponent.name = name;
    return npc;
}

void setup(std::unique_ptr<Engine> &engine)
{
    for (int i = 0; i < 100; i ++) {
        std::shared_ptr<Entity> npc = createNPC(engine, 3, 3, "NPC" + std::to_string(i));
        auto &npcComponent = npc->getComponent<NPC>();
        npcComponent.pattern = std::make_shared<LinePattern>(LinePattern({3, 3 + i}, {8, 3 + i}));
    }
}

int start_engine() {
    sf::Clock clock;
    float timeElapsed = 0;
    bool isRunning = true;
    
    std::unique_ptr<Engine> engine = std::make_unique<Engine>();
    engine->start();

    setup(engine);

    NetworkServer server;
    server.host(53000);

    while (isRunning) {
        float deltaTime = clock.restart().asSeconds();

        std::string inputs = server.receivePacket();

        std::vector<NetworkEvent> events = engine->parseServerInput(inputs);
        std::vector<NetworkEvent> events2 = engine->update(deltaTime);

        events.insert(events.end(), events2.begin(), events2.end());
        server.processEngineInput(events);
    }
    return 0;
}

int main(int argc, char** argv)
{
    (void)argv;
    std::cout << "Starting server..." << std::endl;
    return start_engine();
}
