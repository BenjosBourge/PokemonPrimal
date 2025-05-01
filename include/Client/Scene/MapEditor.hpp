/*
** Pokemon Primal
** File description:
** MapEditor
*/

#pragma once

#include <Scene/IScene.hpp>
#include <Objects/Map.hpp>
#include <Game.hpp>

#include <iostream>
#include <memory>
#include <array>
#include <unordered_map>
#include <cmath>


class MapEditor : public IScene {
    public:
        MapEditor();
        ~MapEditor();

        void draw(Game &game) override;
        void update(float deltaTime) override;
    private:
        sf::VertexArray _vertices;
        sf::Texture _tileset;
        Map _spriteMap;
};
