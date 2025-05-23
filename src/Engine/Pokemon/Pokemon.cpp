/*
** Pokemon Primal
** File description:
** Pokemon
*/

#include <Pokemon/Pokemon.hpp>
#include <iostream>

Pokemon::Pokemon()
{
    _name = "Default";
    _id = PokemonId::NULL_POKEMON;
    _level = 1;
    _exp = 0;

    _hp = 1;
    _attack = 1;
    _defense = 1;
    _speAttack = 1;
    _speDefense = 1;
    _speed = 1;

    actualizeCurrentStats();
    _currentHp = _maxHp;

    _type1 = Type::NORMAL;
    _type2 = Type::NULL_TYPE;

    _moves[0] = pokemonMoves[SCRATCH];
    _moves[1] = pokemonMoves[NULL_MOVE];
    _moves[2] = pokemonMoves[NULL_MOVE];
    _moves[3] = pokemonMoves[NULL_MOVE];
}

Pokemon::Pokemon(std::string name, int hp, int attack, int defense, int speAttack, int speDefense, int speed, Type type1, Type type2) : Pokemon()
{
    _hp = hp;
    _attack = attack;
    _defense = defense;
    _speAttack = speAttack;
    _speDefense = speDefense;
    _speed = speed;

    actualizeCurrentStats();
    _currentHp = _maxHp;

    _type1 = type1;
    _type2 = type2;
}

Pokemon::Pokemon(std::string name, int hp, int attack, int defense, int speAttack, int speDefense, int speed, Type type1) : Pokemon()
{
    _hp = hp;
    _attack = attack;
    _defense = defense;
    _speAttack = speAttack;
    _speDefense = speDefense;
    _speed = speed;

    actualizeCurrentStats();
    _currentHp = _maxHp;

    _type1 = type1;
    _type2 = Type::NULL_TYPE;
}

Pokemon::~Pokemon()
{

}


//combat
void Pokemon::takeDamage(Pokemon &attacker, PokemonMove &move)
{
    auto attack = float(attacker._currentAttack);
    auto defense = float(_currentDefense);
    auto power = float(move._power);

    if (move._spe) {
        attack = float(attacker._currentSpeAttack);
        defense = float(_currentSpeDefense);
    }

    //apply modifier except for critical hit

    float damage = ((2.*float(attacker._level) / 5. + 2.) * power * attack / defense) / 50. + 2.;

    if (move._type == attacker._type1 || move._type == attacker._type2) {
        damage *= 1.5;
    }

    damage *= typeEffectiveness(move._type);

    int damageInt = int(damage + 0.5);
    std::cout << "DamageInt: " << damageInt << std::endl;
    if (damageInt < 0)
        damageInt = 0;

    if (damageInt > _currentHp)
        _currentHp = 0;
    else
        _currentHp -= damageInt;
}

float Pokemon::typeEffectiveness(Type type)
{
    float effectiveness = 1.0;

    effectiveness *= typeTable[_type1][type];
    if (_type2 != Type::NULL_TYPE) {
        effectiveness *= typeTable[_type2][type];
    }

    return effectiveness;
}


//stats
int Pokemon::getCurrentStatFromLevel(int stat)
{
    int iv = 0;
    int ev = 0;

    int result = (2 * stat + iv + (ev / 4)) * _level / 100 + 5;
    return result;
}

int Pokemon::getCurrentHpFromLevel(int stat)
{
    int iv = 0;
    int ev = 0;

    int result = (2 * stat + iv + (ev / 4)) * _level / 100 + _level + 10;
    return result;
}

void Pokemon::actualizeCurrentStats()
{
    _maxHp = getCurrentHpFromLevel(_hp);
    _currentAttack = getCurrentStatFromLevel(_attack);
    _currentDefense = getCurrentStatFromLevel(_defense);
    _currentSpeAttack = getCurrentStatFromLevel(_speAttack);
    _currentSpeDefense = getCurrentStatFromLevel(_speDefense);
    _currentSpeed = getCurrentStatFromLevel(_speed);
}