/*
** Pokemon Primal
** File description:
** SceneEditor
*/

#include <Scene/MapEditor.hpp>


MapEditor::MapEditor()
{
    _cameraView.setSize({1280, 720}); // Adjust based on your window size
    _cameraView.setCenter({640, 360}); // Center of the view

    _spriteMap.load(
        "assets/tilesmap.png", 
        {static_cast<unsigned>(_tileSize), static_cast<unsigned>(_tileSize)},
        createBitMap(12288, 192)
    );
    
    _selector.setSize({_tileSize, _tileSize});
    _selector.setFillColor(sf::Color(255, 0, 0, 100));
    _selector.setOutlineThickness(1);
    _selector.setOutlineColor(sf::Color(255, 0, 0, 255));
    _selector.setPosition(sf::Vector2f{0.0, 0.0});

    //_HUD->setGrid(_spriteMap);
}

MapEditor::~MapEditor()
{

}

void MapEditor::draw(sf::RenderWindow *window)
{
    window->setView(_cameraView);
    window->draw(_spriteMap);
    window->draw(_selector);
    _HUD->draw(*window);
}

void MapEditor::update(float deltaTime) {
    _moveCooldown -= deltaTime;
    if (_moveCooldown <= 0.f) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            _selector.setPosition({_selector.getPosition().x, _selector.getPosition().y + _tileSize});
            _moveCooldown = _moveInterval;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
            _selector.setPosition({_selector.getPosition().x, _selector.getPosition().y - _tileSize});
            _moveCooldown = _moveInterval;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            _selector.setPosition({_selector.getPosition().x - _tileSize, _selector.getPosition().y});
            _moveCooldown = _moveInterval;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            _selector.setPosition({_selector.getPosition().x + _tileSize, _selector.getPosition().y});
            _moveCooldown = _moveInterval;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        _cameraView.move({0, -_cameraSpeed * deltaTime});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        _cameraView.move({0, _cameraSpeed * deltaTime});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        _cameraView.move({-_cameraSpeed * deltaTime, 0});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        _cameraView.move({_cameraSpeed * deltaTime, 0});

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) {
        _cameraView.zoom(0.9f);  // Zoom in
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
        _cameraView.zoom(1.1f);  // Zoom out
    }

    //reset parameters
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        _cameraView.setCenter({960, 540}); 
        _cameraView.setSize({1920, 1080});
        _selector.setPosition({0, 0});

    }

    
}

void MapEditor::handleEvent(const std::optional<sf::Event> &event) {
    if (const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
    {
        if (mouseWheelScrolled->delta > 0)
            _cameraView.zoom(0.9f);  // Zoom in
        else
            _cameraView.zoom(1.1f);  // Zoom out
    }
}

std::vector<std::vector<int>> MapEditor::createBitMap(int totalElements, int elementsPerRow)
{
    const int numRows = std::ceil(totalElements / static_cast<float>(elementsPerRow));
    int value = 0;

    std::vector<std::vector<int>> _bitMap(numRows);

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < elementsPerRow && value < totalElements; ++col) {
            _bitMap[row].push_back(value++);
        }
    }
    return _bitMap;
}