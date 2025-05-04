/*
** Pokemon Primal
** File description:
** Character
*/

#pragma once
#include <SFML/Graphics.hpp>
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

    void update(float deltaTime) override;

    void setDirection(Direction direction);
    void setAnimationState(AnimationState state);
    void resetYOffset();

    void moveTo(int x, int y);

    void setMotion(bool inMotion) { _inMotion = inMotion; }

protected:
    int _x = 0;
    int _y = 0;
    Direction _direction;
    AnimationState _animationState;

    float _timeTakenAnimation;
    float _currentTimeAnimation;

    int _ox;
    int _oy;

    bool _inMotion;
};

