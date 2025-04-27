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
#include <string>
#include <NetworkClient.hpp>


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
    void inputHandling();

    void parseClientInput(const std::string &data);
    void processToken(const std::string &token);

private:
    sf::RenderWindow window;
    std::string assetsPath;
    NetworkClient _client;

    bool _upPressed;
    bool _downPressed;
    bool _leftPressed;
    bool _rightPressed;
};

#endif /* !GAME_HPP_ */
