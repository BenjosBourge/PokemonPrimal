/*
** Pokemon Primal
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#pragma once

#include <GUI/HUD/HUDComponents/IComponent.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>

class Button : public IComponent {
    public:
        Button(sf::Vector2f position = {0, 0}, sf::Vector2f size = {100, 50}, std::string text = "Button") {
            _shape.setPosition(position);
            _shape.setSize(size);
            _shape.setFillColor(sf::Color::Black);
            _shape.setOutlineThickness(2);

            _text.setPosition({_shape.getPosition().x,
                _shape.getPosition().y}
              );
        };

        ~Button() = default;

        void draw(sf::RenderWindow &window) {
            window.draw(_shape);
            window.draw(_text);
        };

    protected:
    private:
        sf::Text _text = sf::Text(globalFont, "Some Text", 20);
        sf::RectangleShape _shape;
};

#endif /* !BUTTON_HPP_ */