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
#include <Engine/Systems/MvtSystem.hpp>

class Engine {
    private:
        std::vector<std::shared_ptr<ISystem>> _systems;
    public:
        std::shared_ptr<EntityManager> gameObjects;
        EntityFactory _entityFactory;
        Engine();
        ~Engine();
        int addPlayer();
        void update(float deltaTime);
        void clean();
        void start();
        std::string restart(bool &,  int &);
};

#endif /* !ENGINE_HPP_ */
