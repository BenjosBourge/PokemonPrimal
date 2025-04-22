/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <Engine/Entities/EntityManager.hpp>
#include <Engine/Entities/EntityFactory.hpp>

#include <Engine/Components/Position.hpp>
#include <Engine/Components/Input.hpp>

#include <Engine/Systems/MvtSystem.hpp>
#include <Engine/Systems/PlayerMovementSystem.hpp>

#include <Engine/Event.hpp>

class Engine {
private:
    std::vector<std::shared_ptr<ISystem>> _systems;
public:
    std::shared_ptr<EntityManager> gameObjects;
    EntityFactory _entityFactory;

    Engine();
    ~Engine();

    std::vector<NetworkEvent> update(float deltaTime);
    void clean();
    void start();
    std::string restart(bool &,  int &);

    void parseServerInput(const std::string &data);
    void processToken(const std::string &token);
};

#endif /* !ENGINE_HPP_ */
