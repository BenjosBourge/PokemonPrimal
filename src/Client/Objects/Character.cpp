/*
** Pokemon Primal
** File description:
** Character
*/

#include <Objects/Character.hpp>

Character::Character()
{
    _direction = Direction::DOWN;
    _animationState = AnimationState::IDLE;
    _texturePath = "player"; //default value

    _width = 3;
    _height = 3;
    _rectX = 16;
    _rectY = 24;
    _spriteX = 0;
    _spriteY = 0;
}

Character::Character(CharacterTexture texture)
{
    _direction = Direction::DOWN;
    _animationState = AnimationState::IDLE;


    if (texture == CharacterTexture::PLAYER)
        _texturePath = "player";

    _width = 3;
    _height = 3;
    _rectX = 16;
    _rectY = 24;
    _spriteX = 0;
    _spriteY = 0;
}

Character::~Character()
{

}

void Character::setDirection(Direction direction)
{
    _direction = direction;
    resetYOffset();
}

void Character::setAnimationState(AnimationState state)
{
    _animationState = state;
    resetYOffset();
}

void Character::resetYOffset()
{
    _flipped = false;
    if (_direction == Direction::UP)
        _offsetY = 0;
    else if (_direction == Direction::DOWN)
        _offsetY = 3;
    else if (_direction == Direction::LEFT) {
        _offsetY = 6;
    } else if (_direction == Direction::RIGHT) {
        _offsetY = 6;
        _flipped = true;
    }

    if (_animationState == AnimationState::WALKING) {
        setLoop(4, 0.2);
        _offsetY += 1;
    } else if (_animationState == AnimationState::RUNNING) {
        setLoop(4, 0.1);
        _offsetY += 2;
    } else {
        setLoop(1, 0.1);
        _currentFrame = 0;
    }
}

void Character::moveTo(int x, int y)
{
    _x = x;
    _y = y;
    _spriteX = x * 24;
    _spriteY = y * 24;
}