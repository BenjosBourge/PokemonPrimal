/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** Game
*/

#include <SFML/Graphics.hpp>
#include <Graph/Game.hpp>

Game::Game(std::string assetsPath) {
    this->assetsPath = assetsPath;
    this->window.setFramerateLimit(60);
}

Game::~Game()
{
    this->window.close();
}

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Pokemon Primal");
    _client.connect("127.0.0.1", 53000);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        inputHandling();
        _client.receivePacket();

        window.clear();
        window.display();
    }
}

void Game::inputHandling()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
        if (!_upPressed)
            _client.sendPacket("up_pressed");
        _upPressed = true;
    } else {
        if (_upPressed)
            _client.sendPacket("up_released");
        _upPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        if (!_downPressed)
            _client.sendPacket("down_pressed");
        _downPressed = true;
    } else {
        if (_downPressed)
            _client.sendPacket("down_released");
        _downPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
        if (!_leftPressed)
            _client.sendPacket("left_pressed");
        _leftPressed = true;
    } else {
        if (_leftPressed)
            _client.sendPacket("left_released");
        _leftPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        if (!_rightPressed)
            _client.sendPacket("right_pressed");
        _rightPressed = true;
    } else {
        if (_rightPressed)
            _client.sendPacket("right_released");
        _rightPressed = false;
    }
}
