/*
** Pokemon Primal
** File description:
** HUDMenu
*/

#pragma once

#include <Graph/GUI/IHUD.hpp>
#include <Graph/GUI/HUDComponents/Button.hpp>

class HUDMenu : public IHUD {
    public:
        HUDMenu() {
            //add a Icomponenet
            _components.fill(_button);
        };
        ~HUDMenu() {};

        void draw(sf::RenderWindow &window) {
            for (auto &component : _components) {
                component->draw(window);
            }
        };
    protected:

    private:
        std::array<std::shared_ptr<IComponent>, 3> _components;
        std::shared_ptr<Button> _button = std::make_shared<Button>(sf::Vector2f(100, 100), sf::Vector2f(200, 50), "Button");
}; 
