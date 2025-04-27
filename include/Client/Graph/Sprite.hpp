/*
** Pokemon Primal
** File description:
** Sprite
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <Game.hpp>

class Sprite {
public:
    Sprite();
    Sprite(const std::string &texturePath, int x, int y, int width, int height, int rectX, int rectY);
    ~Sprite();

    virtual sf::IntRect getRect(Game &game);
    void draw(Game &game);

    int _x;
    int _y;

    int _rectX;
    int _rectY;

    int _width;
    int _height;
    std::string _texturePath;
};

