/*
** Pokemon Primal
** File description:
** Menu
*/

#include <Scene/Menu.hpp>
#include <Game.hpp>

Menu::Menu()
{
    //add the HUD mennu to the scene
    _hudMenu = std::make_shared<HUDMenu>();
}

void Menu::draw(Game &game)
{
    // Draw the menu
    _hudMenu->draw(*game.getWindow());
}

void Menu::update(float deltaTime)
{
    // Update the menu
}
