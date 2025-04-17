/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** ISystem
*/

#ifndef ISYSTEM_HPP_
    #define ISYSTEM_HPP_
    #include <Engine/Entities/EntityManager.hpp>

    #include <SFML/Graphics.hpp>
    #include <chrono>

    class ISystem {
    public:
        ISystem() = default;
        ~ISystem() = default;

        virtual void update(std::shared_ptr<EntityManager>&, float deltaTime) = 0;
    };

#endif /* !ISYSTEM_HPP_ */
