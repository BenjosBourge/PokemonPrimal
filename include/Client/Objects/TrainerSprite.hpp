/*
** Pokemon Primal
** File description:
** Character
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <Graph/AnimatedSprite.hpp>

#include <Pokemon/Pokemon.hpp>

class TrainerSprite : public Sprite {
public:
    TrainerSprite();
    ~TrainerSprite();

    sf::IntRect getRect() override;

    void update(float deltaTime) override;
    Pokemon _pokemons[6];
    bool _inBattle;
};
