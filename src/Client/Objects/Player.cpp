/*
** Pokemon Primal
** File description:
** Character
*/

#include <Objects/Player.hpp>

Player::Player() : Character()
{

}

Player::Player(CharacterTexture texture) : Character(texture)
{

}

Player::~Player()
{

}

void Player::update(float deltaTime)
{
    Character::update(deltaTime);
}