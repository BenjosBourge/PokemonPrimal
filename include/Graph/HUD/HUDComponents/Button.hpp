/*
** Pokemon Primal
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#pragma once

#include <Graph/HUD/HUDComponents/IComponent.hpp>
#include <SFML/Graphics.hpp>

class Button : public IComponent {
    public:
        Button(sf::Vector2f position = {0, 0}, sf::Vector2f size = {100, 50}, std::string text = "Button") {

            shape.setPosition(position);
            shape.setSize(size);
            shape.setFillColor(sf::Color::Green);
            shape.setOutlineThickness(2);
            shape.setOutlineColor(sf::Color::Black);

        };
        ~Button() = default;
        void draw(sf::RenderWindow &window) {
            window.draw(shape);
        };
    protected:
    private:
        std::string text;
        sf::RectangleShape shape;

        
};

#endif /* !BUTTON_HPP_ */