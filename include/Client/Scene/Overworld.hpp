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
#include <Objects/Player.hpp>
#include <Objects/Character.hpp>
#include <memory>

class Overworld : public IScene {
public:
    Overworld();
    ~Overworld() = default;
    void draw(Game &game);
    void update(float deltaTime);

    void addCharacter(std::string tag);
    std::shared_ptr<Character> getCharacter(std::string tag);

private:
    std::unordered_map<std::string, std::shared_ptr<Character>> _characters;
};
