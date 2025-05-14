/*
** Pokemon Primal
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <Engine/Entities/EntityManager.hpp>
#include <Engine/Entities/EntityFactory.hpp>

#include <Engine/Components/Position.hpp>
#include <Engine/Components/Input.hpp>
#include <Engine/Components/NPC.hpp>

#include <Engine/Systems/MvtSystem.hpp>
#include <Engine/Systems/PlayerMovementSystem.hpp>
#include <Engine/Systems/NPCMovementSystem.hpp>
#include <Engine/Systems/CombatSystem.hpp>

#include <Engine/Event.hpp>

class Engine {
private:
    std::vector<std::shared_ptr<ISystem>> _systems;
public:
    std::shared_ptr<EntityManager> gameObjects;
    EntityFactory _entityFactory;

    std::shared_ptr<Entity> createEntity(std::string name);

    Engine();
    ~Engine();

    std::vector<NetworkEvent> update(float deltaTime);
    void clean();
    void start();
    std::string restart(bool &,  int &);

    std::vector<NetworkEvent> parseServerInput(const std::string &data);
    std::vector<NetworkEvent> processToken(std::string token);
};

#endif /* !ENGINE_HPP_ */
