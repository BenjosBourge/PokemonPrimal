/*
** Pokemon Primal
** File description:
** Character
*/

#include <Objects/Trainer.hpp>

Trainer::Trainer()
{
    _spriteX = 0;
    _spriteY = 0;
    _rectX = 80;
    _rectY = 80;
    _width = 2;
    _height = 2;
    _texturePath = "pokemon";
    _flipped = false;

    for (int i = 0; i < 6; i++) {
        _pokemons[i] = Pokemon();
    }
}

Trainer::~Trainer()
{
    // Destructor implementation
}

void Trainer::update(float deltaTime)
{
    // Update logic for Trainer
}
