/*
** Pokemon Primal
** File description:
** Pokemon
*/

#include <Pokemon/Pokemon.hpp>

PokemonMove::PokemonMove()
{
    _name = "NULL";
    _id = 0;
    _power = 0;
    _accuracy = 0;
    _pp = 0;
    _type = NULL_TYPE;
    _effect = nullptr;
}

PokemonMove::~PokemonMove()
{

}