/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** Game
*/

#include <Game.hpp>
#include <Graph/GUI/global.hpp>
#include <Scene/Menu.hpp>
#include <Scene/Overworld.hpp>

Game::Game()
{
    if (!globalFont.openFromFile("assets/fonts/font.ttf"))
        std::cout << "error while creating font" << std::endl;

    //change this to change scene
    _currentState = GameState::STATE_OVERWORLD;
    //add a scene to the map
    _scenes[GameState::STATE_MENU] = std::make_shared<Menu>();
    _scenes[GameState::STATE_OVERWORLD] = std::make_shared<Overworld>();

    _cameraX = 0;
    _cameraY = 0;

    sf::Texture texture;
    if (!texture.loadFromFile("assets/player.png"))
        std::cout << "error while loading texture" << std::endl;
    _textures["player"] = texture;
}

Game::~Game()
{
    this->_window->close();
}

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Pokemon Primal");
    window.setFramerateLimit(60);
    _window = &window;
    _client.connect("127.0.0.1", 53000);

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        _deltaTime = deltaTime.asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        inputHandling();
        std::string inputs = _client.receivePacket();
        parseClientInput(inputs);

        _scenes[_currentState]->update(_deltaTime);

        window.clear(sf::Color::Black);
        _scenes[_currentState]->draw(*this);
        window.display();
    }
}

void Game::inputHandling()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
        if (!_upPressed)
            _client.sendPacket("Up_P");
        _upPressed = true;
    } else {
        if (_upPressed)
            _client.sendPacket("Up_R");
        _upPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        if (!_downPressed)
            _client.sendPacket("Do_P");
        _downPressed = true;
    } else {
        if (_downPressed)
            _client.sendPacket("Do_R");
        _downPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
        if (!_leftPressed)
            _client.sendPacket("Le_P");
        _leftPressed = true;
    } else {
        if (_leftPressed)
            _client.sendPacket("Le_R");
        _leftPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        if (!_rightPressed)
            _client.sendPacket("Ri_P");
        _rightPressed = true;
    } else {
        if (_rightPressed)
            _client.sendPacket("Ri_R");
        _rightPressed = false;
    }
}

sf::Texture &Game::getTexture(const std::string &texturePath)
{
    if (_textures.find(texturePath) == _textures.end()) {
        std::cout << "No texture found for " << texturePath << std::endl;
        return _textures["player"];
    }
    return _textures[texturePath];
}