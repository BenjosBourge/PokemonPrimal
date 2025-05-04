/*
** Pokemon Primal
** File description:
** MapEditor
*/

#pragma once

#include <Scene/IScene.hpp>
#include <Objects/Map.hpp>
#include <Graph/GUI/HUDMapEditor.hpp>

#include <iostream>
#include <memory>
#include <array>
#include <unordered_map>
#include <cmath>


class MapEditor : public IScene {
    public:
        MapEditor();
        ~MapEditor();

        void draw(sf::RenderWindow *window) override;
        void update(float deltaTime) override;
        std::vector<std::vector<int>> createBitMap(int totalElements, int elementsPerRow);

        void handleEvent(const std::optional<sf::Event> &event);

    private:
        sf::VertexArray _vertices;
        sf::Texture _tileset;
        Map _spriteMap;
        std::shared_ptr<HUDMapEditor> _HUD = std::make_shared<HUDMapEditor>();

        sf::View _cameraView;
        float _cameraSpeed = 500.0f;
        float _zoomLevel = 1.0f;
};
