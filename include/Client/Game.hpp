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
#include <Scene/IScene.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <NetworkClient.hpp>


enum class GameState {
    STATE_DEFAULT,
    STATE_MENU
};

class Game {
public:
    Game();
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

    std::string _assetsPath;

    GameState _currentState;
    std::map<GameState, std::shared_ptr<IScene>> _scenes;
};

#endif /* !GAME_HPP_ */
