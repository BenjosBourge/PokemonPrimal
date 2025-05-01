/*
** Pokemon Primal
** File description:
** Sprite
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <Graph/Sprite.hpp>

class AnimatedSprite : public Sprite {
public:
    AnimatedSprite();
    AnimatedSprite(const std::string &texturePath, int x, int y, int width, int height, int rectX, int rectY);
    ~AnimatedSprite();

    sf::IntRect getRect(Game &game) override;
    void setLoop(int frameNb, float timePerFrame);

    int _frameNb;
    int _currentFrame;
    float _timePerFrame;
    float _currentTime;
    int _offsetY;
};

