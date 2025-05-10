/*
** Pokemon Primal
** File description:
** Character
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <Graph/AnimatedSprite.hpp>

#include <Pokemon/Pokemon.hpp>

class Trainer : public Sprite {
public:
    Trainer();
    ~Trainer();

    void update(float deltaTime) override;
    Pokemon _pokemons[6];
};
