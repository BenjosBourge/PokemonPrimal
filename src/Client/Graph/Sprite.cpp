/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** Game
*/

#include <Graph/Sprite.hpp>

Sprite::Sprite()
{
    _x = 0;
    _y = 0;
    _width = 0;
    _height = 0;
    _texturePath = "";
}

Sprite::~Sprite()
{
}

Sprite::Sprite(const std::string &texturePath, int x, int y, int width, int height, int rectX, int rectY)
{
    _x = x;
    _y = y;
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

    sprite.setPosition({(float)_x, (float)_y});
    sprite.setScale({(float)_width, (float)_height});
    sprite.setOrigin({(float)_width / 2, (float)_height / 2});
    sprite.setTextureRect(getRect(game));

    game.getWindow()->draw(sprite);
}

