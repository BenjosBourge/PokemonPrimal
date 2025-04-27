/*
** Pokemon Primal
** File description:
** Input
*/

#pragma once
#include <Engine/Components/IComponent.hpp>
#include <iostream>
#include <SFML/System/Vector2.hpp>

class Input : virtual public IComponent {
public:
    bool _upPressed = false;
    bool _downPressed = false;
    bool _leftPressed = false;
    bool _rightPressed = false;

    Input() {
        _upPressed = false;
        _downPressed = false;
        _leftPressed = false;
        _rightPressed = false;
    }

    ~Input() = default;
};
