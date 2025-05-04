/*
** Pokemon Primal
** File description:
** Game
*/

#include <Game.hpp>

Game::Game()
{
    if (!globalFont.openFromFile("assets/fonts/font.ttf"))
        std::cout << "error while creating font" << std::endl;

    //add a scene to the map
    _scenes[GameState::STATE_MENU] = std::make_shared<Menu>();
    _scenes[GameState::STATE_OVERWORLD] = std::make_shared<Overworld>();
    _scenes[GameState::STATE_MAPEDIT] = std::make_shared<MapEditor>();
    
    //change this to change scene
    _currentState = GameState::STATE_MAPEDIT;
    _cameraX = 0;
    _cameraY = 0;

    sf::Texture texture;
    if (!texture.loadFromFile("assets/player.png"))
        std::cout << "error while loading texture" << std::endl;
    globalTextures._textures["player"] = texture;
}

Game::~Game()
{
    this->_window->close();
}

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Pokemon Primal");
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
            inputHandling(event);  
            _scenes[_currentState]->handleEvent(event);
        }

        std::string inputs = _client.receivePacket();
        parseClientInput(inputs);

        _scenes[_currentState]->update(_deltaTime);

        window.clear(sf::Color::Black);
        _scenes[_currentState]->draw(&window);
        window.display();
    }
}

void Game::inputHandling(const std::optional<sf::Event>& event)
{   
    if (event->is<sf::Event::KeyPressed>()) {
        //find element in the map to execute the function link to the key
        auto it = keyMappings.find(event->getIf<sf::Event::KeyPressed>()->code);
         
        if (it != keyMappings.end() && !it->second.isPressed) {
            if (it->second.type == PRESSED || it->second.type == PRESSED_RELEASED)
                it->second.actionPressed();
            it->second.isPressed = true;
        }
    }

    if (event->is<sf::Event::KeyReleased>()) {
        auto it = keyMappings.find(event->getIf<sf::Event::KeyReleased>()->code);
    
        if (it != keyMappings.end() && it->second.isPressed) {
            if (it->second.type == RELEASED || it->second.type == PRESSED_RELEASED)
                it->second.actionReleased();
            it->second.isPressed = false;
        }
    }
}
