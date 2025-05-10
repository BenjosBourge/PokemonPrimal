/*
** Pokemon Primal
** File description:
** Menu
*/


#pragma once

#include <Scene/IScene.hpp>
#include <Graph/GUI/HUDMenu.hpp>


class Menu : public IScene {
    public:
        Menu();
        ~Menu() = default;
        void draw(sf::RenderWindow *window) override;
        void update(float deltaTime);
        void handleEvent(const std::optional<sf::Event> &event, float deltaTime) {};


    private:
        std::shared_ptr<HUDMenu> _hudMenu;
};
