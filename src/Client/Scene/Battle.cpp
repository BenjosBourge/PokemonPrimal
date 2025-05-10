/*
** Pokemon Primal
** File description:
** Battle
*/

#include <Scene/Battle.hpp>

Battle::Battle()
{
    for (int i = 0; i < 8; i++) {
        std::shared_ptr<Trainer> trainer = std::make_shared<Trainer>();
        if (i < 4) {
            trainer->_spriteX = 100 + i * 100;
            trainer->_spriteY = 500;
            trainer->_texturePath = "pokemon_back";
        } else {
            trainer->_spriteX = 800 + (i - 4) * 100;
            trainer->_spriteY = 100;
        }
        trainers.push_back(trainer);
    }
}

void Battle::draw(sf::RenderWindow *window)
{
    for (auto &trainer : trainers) {
        trainer->draw(window, _cameraX, _cameraY);
    }
}

void Battle::update(float deltaTime)
{
    for (auto &trainer : trainers) {
        trainer->update(deltaTime);
    }
}
