/*
** Pokemon Primal
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Network.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <Graph/Scene/Menu.hpp>

#include <map>
#include <memory>
#include <iostream>
#include <string>

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
    std::string assetsPath;

    GameState currentState;
    std::map<GameState, std::shared_ptr<IScene>> scenes;

};

#endif /* !GAME_HPP_ */
