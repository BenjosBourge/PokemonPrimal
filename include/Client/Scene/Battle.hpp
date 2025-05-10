/*
** Pokemon Primal
** File description:
** Battle
*/

#pragma once

#include <Scene/IScene.hpp>
#include <Objects/Trainer.hpp>

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
    void update(float deltaTime) override;

    void handleEvent(const std::optional<sf::Event> &event){};
private:
    std::vector<std::shared_ptr<Trainer>> trainers;
};
