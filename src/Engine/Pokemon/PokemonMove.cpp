/*
** Pokemon Primal
** File description:
** Pokemon
*/

#include <Pokemon/Pokemon.hpp>

PokemonMove::PokemonMove()
{
    _name = "Default";
    _power = 0;
    _accuracy = 0;
    _pp = 0;
    _type = Type::NULL_TYPE;
}

PokemonMove::~PokemonMove()
{

}