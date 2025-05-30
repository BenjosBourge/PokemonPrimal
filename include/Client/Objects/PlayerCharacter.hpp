/*
** Pokemon Primal
** File description:
** Player
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <Objects/Character.hpp>

class PlayerCharacter : public Character {
public:
    PlayerCharacter();
    PlayerCharacter(CharacterTexture texture);
    ~PlayerCharacter();

    void update(float deltaTime) override;
};

