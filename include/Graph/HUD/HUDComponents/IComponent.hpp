/*
** Pokemon Primal
** File description:
** IComponents
*/

#ifndef ICOMPONENTS_HPP_
#define ICOMPONENTS_HPP_

#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

class IComponent {
    public:
        IComponent() = default;
        virtual ~IComponent() = default;
        virtual void draw(sf::RenderWindow &window) = 0;
    protected:
    private:
};

#endif /* !ICOMPONENTS_HPP_ */