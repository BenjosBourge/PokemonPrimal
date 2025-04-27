/*
** Pokemon Primal
** File description:
** Menu
*/


#pragma once

#include <Scene/IScene.hpp>

#include <iostream>
#include <Graph/AnimatedSprite.hpp>
#include <Graph/Sprite.hpp>
#include <memory>

class Overworld : public IScene {
public:
    Overworld();
    ~Overworld() = default;
    void draw(Game &game);
    void update(float deltaTime);

private:
    std::shared_ptr<Sprite> _test;
    std::shared_ptr<AnimatedSprite> _test2;
};
