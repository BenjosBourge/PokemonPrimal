/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
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


    class EntityFactory {
        public:
            EntityFactory(void);
            ~EntityFactory(void);

            Entity &createEntity(std::string);
    };

#endif /* !ENTITYFACTORY_HPP_ */
