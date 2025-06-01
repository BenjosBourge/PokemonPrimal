/*
** Pokemon Primal
** File description:
** Pokemon
*/

#include <Pokemon/Pokemon.hpp>

void EmberEffect(Pokemon &attacker, Pokemon &defender)
{
    int randomEffect = rand() % 100;
    if (randomEffect < 10) {
        std::cout << attacker._name << " burned " << defender._name << "!" << std::endl;
    } else {
        std::cout << attacker._name << " did not burn " << defender._name << "!" << std::endl;
    }
}
