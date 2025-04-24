/*
** Pokemon Primal
** File description:
** Engine
*/

#pragma once

class Pokemon;

enum PokemonId {
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