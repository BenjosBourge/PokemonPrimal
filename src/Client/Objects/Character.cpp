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
    _currentTimeAnimation = 0;
    _timeTakenAnimation = 0.4f;
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
    _currentTimeAnimation = 0;
    _timeTakenAnimation = 0.4f;
}

Character::~Character()
{

}

void Character::update(float deltaTime)
{
    _currentTimeAnimation += deltaTime;
    if (_currentTimeAnimation >= _timeTakenAnimation) {
        _currentTimeAnimation = 0;
        _ox = _x;
        _oy = _y;
        _spriteX = _ox * TILE_SIZE;
        _spriteY = _oy * TILE_SIZE;
        setAnimationState(AnimationState::IDLE);
    } else {
        int nx = (_x * TILE_SIZE - _ox * TILE_SIZE) * _currentTimeAnimation / _timeTakenAnimation;
        int ny = (_y * TILE_SIZE - _oy * TILE_SIZE) * _currentTimeAnimation / _timeTakenAnimation;
        _spriteX = _ox * TILE_SIZE + nx;
        _spriteY = _oy * TILE_SIZE + ny;
    }
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
    _ox = _x;
    _oy = _y;

    _x = x;
    _y = y;

    if (_x > _ox)
        setDirection(Direction::RIGHT);
    else if (_x < _ox)
        setDirection(Direction::LEFT);
    else if (_y < _oy)
        setDirection(Direction::DOWN);
    else if (_y > _oy)
        setDirection(Direction::UP);

    setAnimationState(AnimationState::WALKING);

    _currentTimeAnimation = 0;
}