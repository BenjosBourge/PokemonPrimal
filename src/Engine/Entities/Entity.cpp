/*
** Pokemon Primal
** File description:
** Entity
*/

#include "Engine/Entities/Entity.hpp"

Entity::Entity() { }

Entity::~Entity() { }

void Entity::addComponent(std::shared_ptr<IComponent> component)
{
    _components[typeid(*component)] = component;
}

void Entity::removeComponent(std::shared_ptr<IComponent> component)
{
    _components.erase(typeid(*component));
}
