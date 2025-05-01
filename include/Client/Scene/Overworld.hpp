/*
** Pokemon Primal
** File description:
** Overworld
*/

#pragma once

#include <Scene/IScene.hpp>
#include <Graph/AnimatedSprite.hpp>
#include <Graph/Sprite.hpp>
#include <Objects/Player.hpp>
#include <Objects/Character.hpp>
#include <Objects/Map.hpp>

#include <iostream>
#include <memory>
#include <array>
#include <unordered_map>
#include <cmath>


class Overworld : public IScene {
    public:
        Overworld();
        ~Overworld() = default;

        void draw(Game &game) override;
        void update(float deltaTime) override;

        void addCharacter(std::string tag);
        std::shared_ptr<Character> getCharacter(std::string tag);

    private:
        std::unordered_map<std::string, std::shared_ptr<Character>> _characters;

        sf::VertexArray _vertices;
        sf::Texture _tileset;
        Map _spriteMap;
};
