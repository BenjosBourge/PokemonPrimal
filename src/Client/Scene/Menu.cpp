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

void Menu::draw(sf::RenderWindow *window)
{
    _hudMenu->draw(*window);
}

void Menu::update(float deltaTime, sf::RenderWindow *window, NetworkClient &client)
{

}
