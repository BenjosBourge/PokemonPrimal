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
            _pokemons[i] = std::make_shared<Pokemon>();
        }
        _attackSelected = -1;
        _name = name;
        _posInCombat = 0;
        _target = 0;
    }
    Trainer() {
        for (int i = 0; i < 6; i++) {
            _pokemons[i] = std::make_shared<Pokemon>();
        }
        _attackSelected = -1;
        _name = "Trainer";
        _posInCombat = 0;
        _target = 0;
    }
    ~Trainer() = default;

    std::shared_ptr<Pokemon> _pokemons[6];
    int _attackSelected;
    std::string _name;
    int _posInCombat;
    int _target;
};
