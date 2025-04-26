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
#include <GUI/global.hpp>

class IComponent {
    public:
        IComponent() = default;
        ~IComponent() = default;
        virtual void draw(sf::RenderWindow &window) = 0;
    protected:
    private:
};

#endif /* !ICOMPONENTS_HPP_ */