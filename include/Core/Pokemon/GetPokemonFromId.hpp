/*
** Pokemon Primal
** File description:
** Engine
*/

#pragma once

class Pokemon;

enum PokemonId {
    NULL_POKEMON,
    BULBASAUR,
    IVYSAUR,
    VENUSAUR,
    CHARMANDER,
    CHARMELEON,
    CHARIZARD,
    SQUIRTLE,
    WARTORTLE,
    BLASTOISE
};

Pokemon getPokemonFromId(PokemonId id);