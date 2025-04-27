/*
** Pokemon Primal
** File description:
** AnimatedSprite
*/

#include <Graph/AnimatedSprite.hpp>

AnimatedSprite::AnimatedSprite() : Sprite()
{
    _frameNb = 0;
    _currentFrame = 0;
    _timePerFrame = 0;
    _currentTime = 0;
}

AnimatedSprite::AnimatedSprite(const std::string &texturePath, int x, int y, int width, int height, int rectX, int rectY) : Sprite(texturePath, x, y, width, height, rectX, rectY)
{
    _frameNb = 0;
    _currentFrame = 0;
    _timePerFrame = 0;
    _currentTime = 0;
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::setLoop(int frameNb, float timePerFrame)
{
    _frameNb = frameNb;
    _currentFrame = 0;
    _timePerFrame = timePerFrame;
    _currentTime = 0;
}

sf::IntRect AnimatedSprite::getRect(Game &game)
{
    sf::IntRect rect = Sprite::getRect(game);

    _currentTime += game.getDeltaTime();
    if (_currentTime >= _timePerFrame) {
        _currentFrame++;
        _currentTime = 0;
        if (_currentFrame >= _frameNb) {
            _currentFrame = 0;
        }
    }

    rect.position.x = _currentFrame * _rectX;
    rect.position.y = _offsetY * _rectY;

    return rect;
}


