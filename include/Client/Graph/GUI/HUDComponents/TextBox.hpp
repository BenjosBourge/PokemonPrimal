/*
** Pokemon Primal
** File description:
** TextBox
*/

#pragma once

#include <Graph/GUI/HUDComponents/IComponent.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>

class TextBox : public IComponent {
public:
    TextBox(sf::Vector2f position = {0, 0}, int size = 10, std::string text = "TextBox") {
        _text.setCharacterSize(size);
        _text.setString(text);
        _text.setPosition(position);
        _visible = true;
    };

    ~TextBox() = default;

    void draw(sf::RenderWindow &window) {
        if (!_visible)
            return;
        window.draw(_text);
    };

    bool _visible;
    sf::Text _text = sf::Text(globalFont, "Some Text", 10);
    sf::RectangleShape _shape;
};
