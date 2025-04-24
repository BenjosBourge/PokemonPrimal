/*
** Pokemon Primal
** File description:
** Pokemon
*/

#include <Pokemon/Pokemon.hpp>

Pokemon::Pokemon()
{
    _name = "Default";
    _id = PokemonId::BULBASAUR;
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