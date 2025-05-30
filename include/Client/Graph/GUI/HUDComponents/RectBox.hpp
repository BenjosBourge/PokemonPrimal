/*
** Pokemon Primal
** File description:
** RectBox
*/


#pragma once

#include <Graph/GUI/HUDComponents/IComponent.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>

class RectBox : public IComponent {
    public:
        RectBox(sf::Vector2f position = {0, 0}, sf::Vector2f size ={16, 16}, sf::Color fillcolor = {0, 0, 0, 0}) {
            _shape.setSize(size);
            _shape.setPosition(position);
            _shape.setFillColor(fillcolor);
            _shape.setOutlineColor(sf::Color::White);
            _shape.setOutlineThickness(1);
        };

        ~RectBox() = default;

        void draw(sf::RenderWindow &window) {
            window.draw(_shape);
        };

    protected:
    private:
        sf::RectangleShape _shape;
};