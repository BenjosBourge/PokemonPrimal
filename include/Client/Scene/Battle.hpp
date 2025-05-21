/*
** Pokemon Primal
** File description:
** Battle
*/

#pragma once

#include <Scene/IScene.hpp>
#include <Objects/TrainerSprite.hpp>
#include <Graph/GUI/HUDBattle.hpp>

#include <iostream>
#include <memory>
#include <array>
#include <unordered_map>
#include <cmath>


class Battle : public IScene {
public:
    Battle();
    ~Battle() = default;

    void draw(sf::RenderWindow *window) override;
    void update(float deltaTime, sf::RenderWindow *window, NetworkClient &client) override;

    void handleEvent(const std::optional<sf::Event> &event, float deltaTime){};

    int _nbTeam1 = 0;
    int _nbTeam2 = 0;

    int _ownPlayer = 0;

    std::vector<std::shared_ptr<TrainerSprite>> _trainers;
    std::shared_ptr<HUDBattle> _hudBattle;
};
