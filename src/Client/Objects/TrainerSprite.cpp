/*
** Pokemon Primal
** File description:
** Character
*/

#include <Objects/TrainerSprite.hpp>

TrainerSprite::TrainerSprite()
{
    _spriteX = 0;
    _spriteY = 0;
    _rectX = 80;
    _rectY = 80;
    _width = 2;
    _height = 2;
    _texturePath = "pokemon";
    _flipped = false;

    for (int i = 0; i < 6; i++) {
        _pokemons[i] = Pokemon();
    }
    _inBattle = false;
}

TrainerSprite::~TrainerSprite()
{
    // Destructor implementation
}

sf::IntRect TrainerSprite::getRect()
{
    sf::IntRect rect = Sprite::getRect();
    int id = _pokemons[0]._id - 1;
    rect.position.x = 80 * id;
    return rect;
}

void TrainerSprite::update(float deltaTime)
{

}
