/*
** Pokemon Primal
** File description:
** Menu
*/

#include <Scene/Overworld.hpp>

Overworld::Overworld()
{
    // Initialize the test sprite
    _test = std::make_shared<Sprite>("player", 100, 100, 3, 3, 16, 24);
    _test2 = std::make_shared<AnimatedSprite>("player", 100, 200, 3, 3, 16, 24);

    _test2->setLoop(4, 0.25f);
    _test2->_offsetY = 1;
}

void Overworld::draw(Game &game)
{
    // Draw the test sprite
    _test->draw(game);
    _test2->draw(game);
}

void Overworld::update(float deltaTime)
{
    // Update the menu
}
