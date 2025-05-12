/*
** Pokemon Primal
** File description:
** Battle
*/

#include <Scene/Battle.hpp>

Battle::Battle()
{
    for (int i = 0; i < 8; i++) {
        std::shared_ptr<TrainerSprite> trainer = std::make_shared<TrainerSprite>();
        if (i < 4) {
            trainer->_spriteX = 100 + i * 100;
            trainer->_spriteY = 500;
            trainer->_texturePath = "pokemon_back";
        } else {
            trainer->_spriteX = 800 + (i - 4) * 100;
            trainer->_spriteY = 100;
        }
        _trainers.push_back(trainer);
    }
    _hudBattle = std::make_shared<HUDBattle>();
}

void Battle::draw(sf::RenderWindow *window)
{
    for (auto &trainer : _trainers) {
        trainer->draw(window, _cameraX, _cameraY);
    }

    _hudBattle->draw(*window);
}

void Battle::update(float deltaTime, sf::RenderWindow *window, NetworkClient &client)
{
    _hudBattle->buttonClicked(window, client);
    for (auto &trainer : _trainers) {
        trainer->update(deltaTime);
    }
}
