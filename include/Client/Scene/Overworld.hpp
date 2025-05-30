/*
** Pokemon Primal
** File description:
** Overworld
*/

#pragma once

#include <Scene/IScene.hpp>
#include <Objects/Map.hpp>

#include <iostream>
#include <memory>
#include <array>
#include <unordered_map>
#include <cmath>

class Character;

class Overworld : public IScene {
public:
    Overworld();
    ~Overworld() = default;

    void draw(sf::RenderWindow *window) override;
    void update(float deltaTime, sf::RenderWindow *window, NetworkClient &client) override;

    void handleEvent(const std::optional<sf::Event> &event, float deltaTime){};

    void addCharacter(std::string tag);
    void removeCharacter(std::string tag);
    std::shared_ptr<Character> getCharacter(std::string tag);

private:
    std::unordered_map<std::string, std::shared_ptr<Character>> _characters;

    sf::VertexArray _vertices;
    sf::Texture _tileset;
    Map _spriteMap;
};
