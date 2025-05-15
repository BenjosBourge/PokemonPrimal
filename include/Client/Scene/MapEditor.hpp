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
        std::vector<std::vector<int>> createEmptyBitMap(int totalElements, int elementsPerRow);
        void handleEvent(const std::optional<sf::Event> &event, float deltaTime);

    private:
        void updateCamera(float deltaTime);
        void updateCursor(float deltaTime);

        void handleKeyPress(sf::Keyboard::Key code, float deltaTime);
        void writeTileIfValid();
        void resetCamera();
        void saveCurrentTile();

        void printBitMap(const std::vector<std::vector<int>>& bitMap);
        sf::VertexArray _vertices;
        sf::Texture _tileset;

        Map _spriteMap;
        Map _editMap;

        std::vector<std::vector<int>> _emptyBitMap;

        std::shared_ptr<HUDMapEditor> _HUD = std::make_shared<HUDMapEditor>();
        float _tileSize = 16.0;
        sf::View _cameraView;
        float _cameraSpeed = 500.0f;
        float _zoomLevel = 1.0f;

        sf::RectangleShape _cursor;
        float _moveCooldown = 0.05f;
        const float _moveInterval = 0.10f;
        sf::Vector2i _mousePixel;
        sf::Vector2f _worldPos;

        int _currentTile = 0;
        int _savedTile = 0;
        int _viewSelector = 0;

        enum {
            VIEW_SPRITESHEET = 0,
            VIEW_EDIT = 1,
        };

};
