/*
** Pokemon Primal
** File description:
** IScene
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

class Game;

class IScene {
public:
    IScene() = default;
    ~IScene() = default;
    virtual void draw(sf::RenderWindow *window) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void handleEvent(const std::optional<sf::Event> &event) = 0;

protected:
    int _cameraX;
    int _cameraY;
private:
    
};
