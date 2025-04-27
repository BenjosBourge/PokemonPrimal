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
    virtual void draw(Game &game) = 0;
    virtual void update(float deltaTime) = 0;
protected:
private:
    
};
