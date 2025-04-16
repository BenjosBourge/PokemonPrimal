/*
** Pokemon Primal
** File description:
** HUDMenu
*/

#ifndef HUDMENU_HPP_
#define HUDMENU_HPP_

#pragma once

#include <Graph/HUD/IHUD.hpp>
#include <Graph/HUD/HUDComponents/Button.hpp>

class HUDMenu : public IHUD {
    public:
        HUDMenu() {
            components.fill(button);
        };
        ~HUDMenu() = default;

        void draw(sf::RenderWindow &window) {
            for (auto &component : components) {
                component->draw(window);
            }
        };
    protected:

    private:
        std::array<std::shared_ptr<IComponent>, 3> components;
        std::shared_ptr<Button> button = std::make_shared<Button>(sf::Vector2f(100, 100), sf::Vector2f(200, 50), "Button");
}; 

#endif /* !HUDMENU_HPP_ */