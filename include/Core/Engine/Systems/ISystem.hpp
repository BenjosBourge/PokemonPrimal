/*
** Pokemon Primal
** File description:
** ISystem
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_
#include <Engine/Entities/EntityManager.hpp>

#include <SFML/Graphics.hpp>
#include <Engine/Event.hpp>
#include <chrono>
#include <unordered_map>

class ISystem {
public:
    ISystem() = default;
    ~ISystem() = default;

    virtual std::vector<NetworkEvent> update(std::shared_ptr<EntityManager>&, float deltaTime) = 0;
    std::unordered_map<std::string, std::shared_ptr<ISystem>> _systems;
};

#endif /* !ISYSTEM_HPP_ */
