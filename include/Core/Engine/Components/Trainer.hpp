/*
** Pokemon Primal
** File description:
** Input
*/

#pragma once
#include <Engine/Components/IComponent.hpp>
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <Pokemon/Pokemon.hpp>

class Trainer : virtual public IComponent {
public:
    Trainer(std::string name) {
        for (int i = 0; i < 6; i++) {
            _pokemons[i] = Pokemon();
        }
        _attackSelected = -1;
        _name = name;
    }
    Trainer() {
        for (int i = 0; i < 6; i++) {
            _pokemons[i] = Pokemon();
        }
        _attackSelected = -1;
        _name = "Trainer";
    }
    ~Trainer() = default;

    Pokemon _pokemons[6];
    int _attackSelected;
    std::string _name;
};
