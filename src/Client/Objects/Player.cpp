/*
** Pokemon Primal
** File description:
** Character
*/

#include <Objects/PlayerCharacter.hpp>

PlayerCharacter::PlayerCharacter() : Character()
{

}

PlayerCharacter::PlayerCharacter(CharacterTexture texture) : Character(texture)
{

}

PlayerCharacter::~PlayerCharacter()
{

}

void PlayerCharacter::update(float deltaTime)
{
    Character::update(deltaTime);
}