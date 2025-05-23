/*
** Pokemon Primal
** File description:
** Pokemon
*/

#include <Pokemon/Pokemon.hpp>

PokemonMove::PokemonMove()
{
    _name = "NULL";
    _id = NULL_MOVE;
    _power = 0;
    _accuracy = 0;
    _pp = 0;
    _type = NULL_TYPE;
    _effect = nullptr;
    _user = 0;
    _target = 0;
    _spe = false;
}

PokemonMove::PokemonMove(std::string name, PokemonMoveId id, int power, bool spe, int accuracy, int pp,
                           Type type, void (*effect)(Pokemon &attacker, Pokemon &defender)) : PokemonMove()
{
    _name = name;
    _id = id;
    _power = power;
    _accuracy = accuracy;
    _pp = pp;
    _type = type;
    _effect = effect;
    _spe = spe;
}

PokemonMove::~PokemonMove()
{

}