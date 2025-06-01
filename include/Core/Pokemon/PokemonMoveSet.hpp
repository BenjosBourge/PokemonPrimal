/*
** Pokemon Primal
** File description:
** Engine
*/

#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <Pokemon/PokemonMove.hpp>
#include <Pokemon/GetPokemonFromId.hpp>

static std::vector<std::pair<int, PokemonMove>> moveBulbasaur = {
        {1, pokemonMoves[SCRATCH]},
        {7, pokemonMoves[VINE_WHIP]}
};

static std::vector<std::pair<int, PokemonMove>> moveIvysaur = {
        {1, pokemonMoves[SCRATCH]},
        {10, pokemonMoves[VINE_WHIP]}
};

static std::vector<std::pair<int, PokemonMove>> moveVenusaur = {
        {1, pokemonMoves[SCRATCH]},
        {14, pokemonMoves[VINE_WHIP]}
};

static std::vector<std::pair<int, PokemonMove>> moveCharmander = {
    {1, pokemonMoves[SCRATCH]},
    {1, pokemonMoves[SCRATCH]},
    {1, pokemonMoves[SCRATCH]},
    {1, pokemonMoves[SCRATCH]},
    {7, pokemonMoves[EMBER]}
};

static std::vector<std::pair<int, PokemonMove>> moveCharmeleon = {
    {1, pokemonMoves[SCRATCH]},
    {10, pokemonMoves[EMBER]}
};

static std::vector<std::pair<int, PokemonMove>> moveCharizard = {
    {1, pokemonMoves[SCRATCH]},
    {14, pokemonMoves[EMBER]}
};

static std::vector<std::pair<int, PokemonMove>> moveSquirtle = {
    {1, pokemonMoves[SCRATCH]},
    {7, pokemonMoves[BUBBLE]}
};

static std::vector<std::pair<int, PokemonMove>> moveWartortle = {
    {1, pokemonMoves[SCRATCH]},
    {10, pokemonMoves[BUBBLE]}
};

static std::vector<std::pair<int, PokemonMove>> moveBlastoise = {
    {1, pokemonMoves[SCRATCH]},
    {14, pokemonMoves[BUBBLE]}
};


static std::unordered_map<PokemonId, std::vector<std::pair<int, PokemonMove>>> pokemonMoveSets = {
    {PokemonId::BULBASAUR, moveBulbasaur},
    {PokemonId::IVYSAUR, moveIvysaur},
    {PokemonId::VENUSAUR, moveVenusaur},
    {PokemonId::CHARMANDER, moveCharmander},
    {PokemonId::CHARMELEON, moveCharmeleon},
    {PokemonId::CHARIZARD, moveCharizard},
    {PokemonId::SQUIRTLE, moveSquirtle},
    {PokemonId::WARTORTLE, moveWartortle},
    {PokemonId::BLASTOISE, moveBlastoise}
};
