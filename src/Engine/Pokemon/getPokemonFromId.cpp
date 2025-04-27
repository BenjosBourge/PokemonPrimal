/*
** Pokemon Primal
** File description:
** Pokemon
*/

#include <Pokemon/Pokemon.hpp>

Pokemon getPokemonFromId(PokemonId id)
{
    Pokemon pokemon;

    if (id == PokemonId::BULBASAUR)
        pokemon = Pokemon("Bulbasaur", 45, 49, 49, 65, 65, 45, Type::GRASS, Type::POISON);
    else if (id == PokemonId::IVYSAUR)
        pokemon = Pokemon("Ivysaur", 60, 62, 63, 80, 80, 60, Type::GRASS, Type::POISON);
    else if (id == PokemonId::VENUSAUR)
        pokemon = Pokemon("Venusaur", 80, 82, 83, 100, 100, 80, Type::GRASS, Type::POISON);
    else if (id == PokemonId::CHARMANDER)
        pokemon = Pokemon("Charmander", 39, 52, 43, 60, 50, 65, Type::FIRE);
    else if (id == PokemonId::CHARMELEON)
        pokemon = Pokemon("Charmeleon", 58, 64, 58, 80, 65, 80, Type::FIRE);
    else if (id == PokemonId::CHARIZARD)
        pokemon = Pokemon("Charizard", 78, 84, 78, 109, 85, 100, Type::FIRE);
    else if (id == PokemonId::SQUIRTLE)
        pokemon = Pokemon("Squirtle", 44, 48, 65, 50, 64, 43, Type::WATER);
    else if (id == PokemonId::WARTORTLE)
        pokemon = Pokemon("Wartortle", 59, 63, 80, 65, 80, 58, Type::WATER);
    else if (id == PokemonId::BLASTOISE)
        pokemon = Pokemon("Blastoise", 79, 83, 100, 85, 105, 78 ,Type::WATER);

    pokemon._id = id;
    return pokemon;
}