/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
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
#include <string>


enum class GameState {
    //? state who need keyboard events
    StartMenu,
    Playing,
    LobbyCreation,

    //? state who don't need keyboard events
    SpectateState,
    WinState,
    LoseState
};

class Game {
public:
    Game(std::string assetsPath);
    ~Game();

    void run();

private:
    sf::RenderWindow window;
    std::string assetsPath;   
};

#endif /* !GAME_HPP_ */
