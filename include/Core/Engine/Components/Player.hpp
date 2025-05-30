/*
** Pokemon Primal
** File description:
** Input
*/

#pragma once
#include <Engine/Components/IComponent.hpp>
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <Engine/Event.hpp>

class Player : virtual public IComponent {
public:
    ClientState _playerState;

    Player() {
        _playerState = ClientState::CLIENT_OVERWORLD;
    }

    ~Player() = default;
};
