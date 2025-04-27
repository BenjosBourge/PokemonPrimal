/*
** Pokemon Primal
** File description:
** Character
*/

#pragma once
#include <SFML/Graphics.hpp>

#include <Game.hpp>
#include <Graph/AnimatedSprite.hpp>

enum CharacterTexture {
    PLAYER
};

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum AnimationState {
    IDLE,
    WALKING,
    RUNNING
};

class Character : public AnimatedSprite {
public:
    Character();
    Character(CharacterTexture texture);
    ~Character();

    void setDirection(Direction direction);
    void setAnimationState(AnimationState state);
    void resetYOffset();

    void moveTo(int x, int y);

private:
    int _x = 0;
    int _y = 0;
    Direction _direction;
    AnimationState _animationState;
};

