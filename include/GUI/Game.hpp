/*
** Pokemon Primal
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#pragma once

#include <map>
#include <memory>
#include <iostream>
#include <string>
#include <optional>

#include <SFML/Network.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <GUI/Scene/Menu.hpp>
#include <GUI/global.hpp>

enum class GameState {
    stateMenu,
    stateFight,
};

class Game {
    public:
        Game(std::string assetsPath);
        ~Game();
        void run();

    private:
    std::string _assetsPath;

    GameState _currentState;
    std::map<GameState, std::shared_ptr<IScene>> _scenes;

};

#endif /* !GAME_HPP_ */
