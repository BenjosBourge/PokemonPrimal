/*
** Pokemon Primal
** File description:
** Game
*/

#include <GUI/Game.hpp>

Game::Game(std::string assetsPath)
{
    this->_assetsPath = assetsPath + "/src/GUI/fonts/font.ttf";
    //Use the global vairable to open the asset
    if (!globalFont.openFromFile(_assetsPath))
        std::cout << "error while creating font" << std::endl;

    //change this to change scene
    _currentState = GameState::stateMenu;
    //add a scene to the map
    _scenes[GameState::stateMenu] = std::make_shared<Menu>();
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
        _scenes[_currentState]->draw(window);
        window.display();
    }
}
