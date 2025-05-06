/*
** Pokemon Primal
** File description:
** EntityFactory
*/

#ifndef ENTITYFACTORY_HPP_
#define ENTITYFACTORY_HPP_

#include <memory>
#include <fstream>
#include <iostream>
#include <Engine/Entities/Entity.hpp>
#include <Engine/Components/Position.hpp>
#include <Engine/Components/Input.hpp>
#include <Engine/Components/NPC.hpp>

class EntityFactory {
public:
    EntityFactory(void);
    ~EntityFactory(void);

    Entity &createEntity(std::string);
};

#endif /* !ENTITYFACTORY_HPP_ */
