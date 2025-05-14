/*
** Pokemon Primal
** File description:
** Engine
*/

#include <Engine/Engine.hpp>

Engine::Engine()
{
    gameObjects = std::make_shared<EntityManager>();
}

Engine::~Engine() { }

void Engine::start()
{
    _entityFactory = EntityFactory();

    std::vector<std::pair<std::string, std::shared_ptr<ISystem>>> pairs;

    pairs.push_back({"MvtSystem", std::make_shared<MvtSystem>()});
    pairs.push_back({"PlayerMovementSystem", std::make_shared<PlayerMovementSystem>()});
    pairs.push_back({"NPCMovementSystem", std::make_shared<NPCMovementSystem>()});
    pairs.push_back({"CombatSystem", std::make_shared<CombatSystem>()});

    std::unordered_map<std::string, std::shared_ptr<ISystem>> systems;
    for (auto &pair : pairs) {
        systems[pair.first] = pair.second;
        _systems.push_back(pair.second);
    }
    for (auto &system : _systems)
        system->_systems = systems;
}

std::string Engine::restart(bool &startGame, int &lastEntityId) 
{
    return "restart";
}

void Engine::clean()
{
    for (auto &entity : gameObjects->entitiesToDestroy) {
        gameObjects->destroyEntity(*entity);
    }
    gameObjects->entitiesToDestroy.clear();
    gameObjects->entitiesDamaged.clear();
}

std::vector<NetworkEvent> Engine::update(float deltaTime)
{
    std::vector<NetworkEvent> output;

    for (auto &system : _systems) {
        std::vector<NetworkEvent> events = system->update(gameObjects, deltaTime);
        if (events.empty())
            continue;
        output.insert(output.end(), events.begin(), events.end());
    }

    return output;
}

std::shared_ptr<Entity> Engine::createEntity(std::string name)
{
    int id = gameObjects->createEntity(_entityFactory.createEntity(name));
    std::shared_ptr<Entity> newEntity = gameObjects->getEntityById(id);

    return newEntity;
}
