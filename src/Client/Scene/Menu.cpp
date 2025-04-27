/*
** Pokemon Primal
** File description:
** Menu
*/

#include <Scene/Menu.hpp>

Menu::Menu()
{
    //add the HUD mennu to the scene
    _hudMenu = std::make_shared<HUDMenu>();
}

void Menu::draw(sf::RenderWindow &window)
{
    // Draw the menu
    _hudMenu->draw(window);                          
}
