/*
** Pokemon Primal
** File description:
** Game
*/

#include <Graph/Game.hpp>

Game::Game(std::string assetsPath)
{
    this->assetsPath = assetsPath;
    currentState = GameState::stateMenu;
    scenes[GameState::stateMenu] = std::make_shared<Menu>();
}

Game::~Game()
{
}

void Game::run()
{

    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(mode, "Pokemon Primal");
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
        // Draw the current scene
        // Update the window
        scenes[currentState]->draw(window);
        window.display();
    }
}
