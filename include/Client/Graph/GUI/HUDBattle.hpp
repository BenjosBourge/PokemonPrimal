/*
** Pokemon Primal
** File description:
** HUDMapEditor
*/

#pragma once

#include <Graph/GUI/IHUD.hpp>
#include <Graph/GUI/HUDComponents/TextBox.hpp>
#include <Graph/GUI/HUDComponents/Button.hpp>
#include <Objects/Map.hpp>
#include <string>
#include <cmath>

class HUDBattle : public IHUD {
public:
    HUDBattle()
    {
        _components.push_back(std::make_shared<Button>(sf::Vector2f(700, 500), sf::Vector2f(220, 120), "Attack 01"));
        _components.push_back(std::make_shared<Button>(sf::Vector2f(940, 500), sf::Vector2f(220, 120), "Attack 02"));
        _components.push_back(std::make_shared<Button>(sf::Vector2f(700, 660), sf::Vector2f(220, 120), "Attack 03"));
        _components.push_back(std::make_shared<Button>(sf::Vector2f(940, 660), sf::Vector2f(220, 120), "Attack 04"));
    };
    ~HUDBattle() = default;


    void draw(sf::RenderWindow &window) override
    {
        for (auto &component : _components) {
            component->draw(window);
        }
    };
protected:

private:
    std::vector<std::shared_ptr<IComponent>> _components;
};