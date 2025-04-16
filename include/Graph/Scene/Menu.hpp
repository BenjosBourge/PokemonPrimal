/*
** Pokemon Primal
** File description:
** Menu
*/


#ifndef MENU_HPP_
#define MENU_HPP_

#pragma once

#include <Graph/Scene/IScene.hpp>
#include <Graph/HUD/HUDMenu.hpp>

#include <iostream>

class Menu : public IScene {
    public:
        Menu();
        ~Menu() = default;
        void draw(sf::RenderWindow &window);

    private:
        std::shared_ptr<HUDMenu> hudMenu;
    

        
};

#endif /* !MENU_HPP_ */
