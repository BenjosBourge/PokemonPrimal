/*
** Pokemon Primal
** File description:
** Menu
*/

#include <Graph/Scene/Menu.hpp>

Menu::Menu()
{
    hudMenu = std::make_shared<HUDMenu>();
}

void Menu::draw(sf::RenderWindow &window)
{
    // Draw the menu
    hudMenu->draw(window);
    std::cout << "Drawing Menu" << std::endl;
}
