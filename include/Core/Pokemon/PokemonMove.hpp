/*
** Pokemon Primal
** File description:
** Engine
*/

#pragma once
#include <string>
#include <Pokemon/PokemonType.hpp>
#include <unordered_map>

class Pokemon;

enum PokemonMoveId {
    NULL_MOVE,
    SCRATCH
};

class PokemonMove {
public:
    PokemonMove();
    PokemonMove(std::string name, PokemonMoveId id, int power, int accuracy, int pp,
                Type type, void (*effect)(Pokemon &attacker, Pokemon &defender));
    ~PokemonMove();

    std::string _name;
    PokemonMoveId _id;
    int _power;
    int _accuracy;
    int _pp;
    Type _type;
    void (* _effect)(Pokemon &attacker, Pokemon &defender);
};

static std::unordered_map<PokemonMoveId, PokemonMove> pokemonMoves = {
    {NULL_MOVE, PokemonMove("NULL", NULL_MOVE, 0, 0, 0, NULL_TYPE, nullptr)},
    {SCRATCH, PokemonMove("Scratch", SCRATCH, 40, 100, 35, NORMAL, nullptr)}
};

