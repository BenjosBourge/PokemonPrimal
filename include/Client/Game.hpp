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

#include <optional>
#include <utility>

#define TILE_SIZE 48

enum class GameState {
    STATE_DEFAULT,
    STATE_MENU,
    STATE_OVERWORLD,
};

class Game {
public:
    Game();
    ~Game();

    void run();
    void inputHandling(const std::optional<sf::Event>& event);


    void parseClientInput(const std::string &data);
    void processToken(const std::string &token);

    sf::Texture &getTexture(const std::string &texturePath);
    sf::RenderWindow *getWindow() { return _window; }
    float getDeltaTime() const { return _deltaTime; }

private:
    sf::RenderWindow *_window;
    int _cameraX;
    int _cameraY;
    float _deltaTime;
    int _cycle; // looping on four digits (0-3) for one second. Useful to synchronize animation later on.

    std::string assetsPath;
    NetworkClient _client;
    std::string _assetsPath;

    GameState _currentState;
    std::map<GameState, std::shared_ptr<IScene>> _scenes;
    std::map<std::string, sf::Texture> _textures;

    enum KeyActionType {
        PRESSED,
        RELEASED,
        PRESSED_RELEASED
    };

    struct KeyAction {
        std::function<void()> actionPressed;
        std::function<void()> actionReleased;
        bool isPressed;
        KeyActionType type;
    };
    
    std::map<sf::Keyboard::Key, KeyAction> keyMappings = {
        {sf::Keyboard::Key::Z, { [&]() { _client.sendPacket("Up_P"); }, [&]() { _client.sendPacket("Up_R"); },  false, PRESSED_RELEASED}},
        {sf::Keyboard::Key::S, { [&]() { _client.sendPacket("Do_P"); }, [&]() { _client.sendPacket("Do_R"); }, false, PRESSED_RELEASED}},
        {sf::Keyboard::Key::D, { [&]() { _client.sendPacket("Ri_P"); }, [&]() { _client.sendPacket("Ri_R"); }, false, PRESSED_RELEASED}},
        {sf::Keyboard::Key::Q, { [&]() { _client.sendPacket("Le_P"); }, [&]() { _client.sendPacket("Le_R"); }, false, PRESSED_RELEASED}},
    };   
};

#endif /* !GAME_HPP_ */
