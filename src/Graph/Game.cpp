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
    this->window.setFramerateLimit(60);
}

Game::~Game()
{
    this->window.close();
}

void Game::run()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");
 
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }
 
        // Clear screen
        window.clear();
 
        // Update the window
        window.display();
    }
}
