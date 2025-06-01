/*
** Pokemon Primal
** File description:
** Engine
*/

#pragma once
#include <string>
#include <Pokemon/PokemonType.hpp>
#include <unordered_map>
#include <iostream>

class Pokemon;

void EmberEffect(Pokemon &attacker, Pokemon &defender);

enum PokemonMoveId {
    NULL_MOVE,
    SCRATCH,
    EMBER,
    VINE_WHIP,
    BUBBLE
};

class PokemonMove {
public:
    PokemonMove();
    PokemonMove(std::string name, PokemonMoveId id, int power, bool spe, int accuracy, int pp,
                Type type, void (*effect)(Pokemon &attacker, Pokemon &defender));
    ~PokemonMove();

    std::string _name;
    PokemonMoveId _id;
    int _power;
    int _accuracy;
    int _pp;
    Type _type;
    void (* _effect)(Pokemon &attacker, Pokemon &defender);
    int _user;
    int _target;
    bool _spe;
};

static std::unordered_map<PokemonMoveId, PokemonMove> pokemonMoves = {
    {NULL_MOVE, PokemonMove("NULL", NULL_MOVE, 0, false, 0, 0, NULL_TYPE, nullptr)},
    {SCRATCH, PokemonMove("Scratch", SCRATCH, 40, false, 100, 35, NORMAL, nullptr)},
    {EMBER, PokemonMove("Ember", EMBER, 40, true, 100, 25, FIRE, EmberEffect)},
    {VINE_WHIP, PokemonMove("Vine Whip", VINE_WHIP, 45, false, 100, 25, GRASS, nullptr)},
    {BUBBLE, PokemonMove("Bubble", BUBBLE, 20, false, 100, 30, WATER, nullptr)} //Bubble has to hit in zone
};

