/*
** Pokemon Primal
** File description:
** IComponents
*/

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <global.hpp>

class IComponent {
    public:
        IComponent() = default;
        ~IComponent() = default;
        virtual void draw(sf::RenderWindow &window) = 0;
    protected:
    private:
};
