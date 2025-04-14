/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** Game
*/

#include <Graph/Game.hpp>

Game::Game(std::string assetsPath)
{
    this->assetsPath = assetsPath;
    this->window.create(sf::VideoMode(1920, 1080), "R-Type", sf::Style::Default);
    this->window.setFramerateLimit(60);
}

Game::~Game()
{
    this->window.close();
}

void Game::run()
{
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        window.display();
    }
}
