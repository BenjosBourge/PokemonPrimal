/*
** Pokemon Primal
** File description:
** Player
*/

#pragma once
#include <SFML/Graphics.hpp>

#include <Game.hpp>
#include <Objects/Character.hpp>

class Player : public Character {
public:
    Player();
    Player(CharacterTexture texture);
    ~Player();
};

