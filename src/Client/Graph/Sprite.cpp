/*
** Pokemon Primal
** File description:
** Sprite
*/

#include <Graph/Sprite.hpp>

Sprite::Sprite()
{
    _spriteX = 0;
    _spriteY = 0;
    _width = 0;
    _height = 0;
    _texturePath = "";
    _flipped = false;
    _rectX = 32;
    _rectY = 32;
}

Sprite::~Sprite()
{
}

Sprite::Sprite(const std::string &texturePath, int x, int y, int width, int height, int rectX, int rectY)
{
    _spriteX = x;
    _spriteY = y;
    _width = width;
    _height = height;
    _texturePath = texturePath;
    _rectX = rectX;
    _rectY = rectY;
}

sf::IntRect Sprite::getRect(Game &game)
{
    return sf::IntRect({0, 0}, {_rectX, _rectY});
}

void Sprite::draw(Game &game)
{
    sf::Sprite sprite(game.getTexture(_texturePath));

    sprite.setPosition({(float)_spriteX, (float)_spriteY});
    if (_flipped)
        sprite.setScale({-(float)_width, (float)_height});
    else
        sprite.setScale({(float)_width, (float)_height});
    sf::Vector2f origin = {(float)_rectX / 2, (float)_rectY / 2};
    sprite.setOrigin(origin);
    sprite.setTextureRect(getRect(game));

    game.getWindow()->draw(sprite);
}

