/*
** Pokemon Primal
** File description:
** Engine
*/

#pragma once
#include <string>
#include <Pokemon/GetPokemonFromId.hpp>

enum Type {
    NULL_TYPE,
    NORMAL,
    FIRE,
    FIGHTING,
    WATER,
    FLYING,
    GRASS,
    POISON,
    ELECTRIC,
    GROUND,
    PSYCHIC,
    ROCK,
    ICE,
    BUG,
    DRAGON,
    GHOST,
    DARK,
    STEEL,
    FAIRY
};

class Pokemon;

class PokemonMove {
public:
    PokemonMove();
    ~PokemonMove();

    std::string _name;
    int _id;
    int _power;
    int _accuracy;
    int _pp;
    Type _type;
    void (* _effect)(Pokemon &attacker, Pokemon &defender);
};

class Pokemon {
public:
    Pokemon();
    Pokemon(std::string name, int hp, int attack, int defense, int speAttack,
            int speDefense, int speed, Type type1, Type type2);
    Pokemon(std::string name, int hp, int attack, int defense, int speAttack,
            int speDefense, int speed, Type type1);
    ~Pokemon();

    std::string _name;
    PokemonId _id;
    int _level;
    int _exp;

    /* Current Stats */
    int getCurrentStatFromLevel(int stat);
    int getCurrentHpFromLevel(int stat);
    void actualizeCurrentStats();

    int _currentHp;
    int _maxHp;

    int _currentAttack;
    int _currentSpeAttack;
    int _currentDefense;
    int _currentSpeDefense;
    int _currentSpeed;

    /* base stats */
    int _hp;
    int _attack;
    int _defense;
    int _speAttack;
    int _speDefense;
    int _speed;

    /* type */
    Type _type1;
    Type _type2;

    /* moves */
    PokemonMove _move1;
    PokemonMove _move2;
    PokemonMove _move3;
    PokemonMove _move4;
};