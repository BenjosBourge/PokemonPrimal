/*
** Pokemon Primal
** File description:
** HUDMapEditor
*/

#pragma once

#include <Graph/GUI/IHUD.hpp>
#include <Graph/GUI/HUDComponents/TextBox.hpp>
#include <Graph/GUI/HUDComponents/Button.hpp>
#include <Graph/GUI/HUDComponents/RectBox.hpp>

#include <Objects/Map.hpp>
#include <string>
#include <cmath>

class HUDMapEditor : public IHUD {
    public:
        HUDMapEditor() {
            _mouseSelector.setSize({16, 16});
            _mouseSelector.setFillColor(sf::Color(255, 0, 0, 100));
            _mouseSelector.setOutlineThickness(1);
            _mouseSelector.setOutlineColor(sf::Color(255, 0, 0, 255));
            _mouseSelector.setPosition(sf::Vector2f{0.0, 0.0});

            
        };
        ~HUDMapEditor() = default;


    void draw(sf::RenderWindow &window) {
        for (auto &component : _components) {
            component->draw(window);
        }
    };

    void setGrid(const Map& map) {
        int elementsPerRow = map._mapSize.x;
        int numRows = map._mapSize.y;
        int value = 0;

        for (int row = 0; row < numRows; ++row) {
            for (int col = 0; col < elementsPerRow; ++col) {
                sf::Vector2f position{
                    static_cast<float>(col * map._tileSize.x),
                    static_cast<float>(row * map._tileSize.y)
                };
                std::shared_ptr<RectBox> rect = std::make_shared<RectBox>(
                    position,
                    sf::Vector2f{16.0, 16.0},
                    sf::Color{0, 0, 0, 0}
                );
                _components.push_back(rect);
                value++;
            }
        }
    }

    int charSize = 7;
    
    protected:

    private:
        int _totalElements;
        int _elementsPerRow;

        sf::RectangleShape _mouseSelector;
        std::shared_ptr<TextBox> textBox = std::make_shared<TextBox>(
            sf::Vector2f{0.0, 0.0}, charSize, "Hello"
        );
        std::vector<std::shared_ptr<IComponent>> _components;

        
};