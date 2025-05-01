/*
** Pokemon Primal
** File description:
** Menu
*/


#pragma once

#include <Scene/IScene.hpp>
#include <Graph/GUI/HUD/HUDMenu.hpp>

#include <iostream>

class Menu : public IScene {
    public:
        Menu();
        ~Menu() = default;
    void draw(sf::RenderWindow *window) override;
        void update(float deltaTime);

    private:
        std::shared_ptr<HUDMenu> _hudMenu;
};
