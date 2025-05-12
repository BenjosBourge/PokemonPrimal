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
        void update(float deltaTime, sf::RenderWindow *window, NetworkClient &client) override;
        std::vector<std::vector<int>> createBitMap(int totalElements, int elementsPerRow);

        void handleEvent(const std::optional<sf::Event> &event);

    private:
        sf::VertexArray _vertices;
        sf::Texture _tileset;
        Map _spriteMap;
        std::shared_ptr<HUDMapEditor> _HUD = std::make_shared<HUDMapEditor>();
        float _tileSize = 16.0;
        sf::View _cameraView;
        float _cameraSpeed = 500.0f;
        float _zoomLevel = 1.0f;

        
        sf::RectangleShape _selector;
        float _moveCooldown = 0.f;
        const float _moveInterval = 0.10f; // 150ms between moves


        // struct KeyAction {
        //     std::function<void()> actionPressed;
        //     std::function<void()> actionReleased;
        //     bool isPressed;
        //     KeyActionType type;
        // };
        
        // std::map<sf::Keyboard::Key, KeyAction> keyMappings = {
        //     {sf::Keyboard::Key::Z, { [&]() { _client.sendPacket("Up_P"); }, [&]() { _client.sendPacket("Up_R"); },  false, PRESSED_RELEASED}},
        //     {sf::Keyboard::Key::S, { [&]() { _client.sendPacket("Do_P"); }, [&]() { _client.sendPacket("Do_R"); }, false, PRESSED_RELEASED}},
        //     {sf::Keyboard::Key::D, { [&]() { _client.sendPacket("Ri_P"); }, [&]() { _client.sendPacket("Ri_R"); }, false, PRESSED_RELEASED}},
        //     {sf::Keyboard::Key::Q, { [&]() { _client.sendPacket("Le_P"); }, [&]() { _client.sendPacket("Le_R"); }, false, PRESSED_RELEASED}},
        // };   
};
