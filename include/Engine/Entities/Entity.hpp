/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** IEntity
*/

#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include <Engine/Components/IComponent.hpp>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeindex>

enum class EntityDeathReason {
    Killed,
    Suicided
};

class Entity {
private:
    std::map<std::type_index, std::shared_ptr<IComponent>> _components;

public:
    int id;
    EntityDeathReason deathReason = EntityDeathReason::Killed;
    Entity();
    ~Entity();
    void addComponent(std::shared_ptr<IComponent> component);
    void removeComponent(std::shared_ptr<IComponent> component);

    template <typename T, typename... Args>
    void createComponent(Args&&... args)
    {
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        addComponent(std::move(component));
    }

    template <typename T>
    void removeComponent(Entity&)
    {
        _components.erase(typeid(T));
    }

    template <typename T>
    T& getComponent()
    {
        auto it = _components.find(typeid(T));
        if (it != _components.end()) {
            auto castedComponent = std::dynamic_pointer_cast<T>(it->second);
            if (castedComponent) {
                return *castedComponent;
            } else {
                throw std::invalid_argument("Component is not of the expected type");
            }
        } else {
            throw std::invalid_argument("Component not found");
        }
    }

    template <typename T>
    bool hasComponent()
    {
        auto it = _components.find(typeid(T));
        if (it != _components.end()) {
            return true;
        } else {
            return false;
        }
    }
};
#endif
