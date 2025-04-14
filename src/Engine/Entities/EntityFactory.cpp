/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rTypeEntity-erwann.laplante
** File description:
** EntityFactory
*/

#include <Engine/Entities/EntityFactory.hpp>

#if defined(_WIN32) || defined(_WIN64)
    #pragma warning(disable: 4244)
#endif

EntityFactory::EntityFactory(void)
{
}

EntityFactory::~EntityFactory() { }

Entity& EntityFactory::createEntity(std::string name)
{
    auto* entity = new Entity();

    if (name == "PowerUpRocketShoot") {
        entity->createComponent<Position>(600, 100, 0, 1);
    
    } else {
    std::cout << "Entity " << name << " not found" << std::endl;
    }   

    return *entity;
}

#if defined(_WIN32) || defined(_WIN64)
    #pragma warning(default: 4244)
#endif
