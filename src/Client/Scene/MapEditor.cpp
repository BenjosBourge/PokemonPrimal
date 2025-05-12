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

    _emptyBitMap = createEmptyBitMap(16, 16);
    _editMap.load(
        "assets/tilesmap.png", 
        {static_cast<unsigned>(_tileSize), static_cast<unsigned>(_tileSize)},
        _emptyBitMap
    );
    
    _cursor.setSize({_tileSize, _tileSize});
    _cursor.setFillColor(sf::Color(255, 0, 0, 100));
    _cursor.setOutlineThickness(1);
    _cursor.setOutlineColor(sf::Color(255, 0, 0, 255));
    _cursor.setPosition(sf::Vector2f{0.0, 0.0});

    _HUD->setGrid(_editMap);
}

MapEditor::~MapEditor()
{

}

void MapEditor::draw(sf::RenderWindow *window)
{   
    _mousePixel = sf::Mouse::getPosition(*window);
    _worldPos = window->mapPixelToCoords(_mousePixel);

    window->setView(_cameraView);

    if (_viewSelector == 1) {
        window->draw(_editMap);
        _HUD->draw(*window);
    }
    else
        window->draw(_spriteMap);

    window->draw(_cursor);
}


void MapEditor::update(float deltaTime)
{
    updateCamera(deltaTime);
    updateCursor(deltaTime);
} 

void MapEditor::handleEvent(const std::optional<sf::Event> &event, float deltaTime) {

    if(const auto* key = event->getIf<sf::Event::KeyPressed>()) {
        // write the tile into the edit map
        if (key->code == sf::Keyboard::Key::Enter && _viewSelector == VIEW_EDIT) {
            _emptyBitMap[_currentTile / _spriteMap._mapSize.x][_currentTile % _spriteMap._mapSize.x] = _savedTile;
            _editMap.reload(_emptyBitMap);
        }
        // change the view to the loaded spritesheet
        if (key->code == sf::Keyboard::Key::Num1) {
            std::cout << "Num1" << std::endl;
            _viewSelector = VIEW_SPRITESHEET;
        }
        // change the view to the edit map
        if (key->code == sf::Keyboard::Key::Num2) {
            _viewSelector = VIEW_EDIT;
        }
        // reset the camera to the default position
        if (key->code == sf::Keyboard::Key::Space) {
            _cameraView.setCenter({960, 540}); 
            _cameraView.setSize({1920, 1080});
            _cursor.setPosition({0, 0});
        }
        // save the current tile
        if (key->code == sf::Keyboard::Key::C) {
            std::cout << "Tile { " << _currentTile << " } is saved" << std::endl;
            _savedTile = _currentTile;
        }
    }
    
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
    if (totalElements == 0) {
        std::vector<std::vector<int>> _bitMap(1);
        return _bitMap;
    }
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

std::vector<std::vector<int>> MapEditor::createEmptyBitMap(int totalElements, int elementsPerRow)
{
    if (totalElements == 0) {
        std::vector<std::vector<int>> _bitMap(1);
        return _bitMap;
    }
    const int numRows = std::ceil(totalElements / static_cast<float>(elementsPerRow));
    int value = 0;
    
    std::vector<std::vector<int>> _bitMap(numRows);
    
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < elementsPerRow && value < totalElements; ++col) {
            _bitMap[row].push_back(0);
        }
    }
    return _bitMap;
}


void MapEditor::updateCamera(float deltaTime)
{
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
}

void MapEditor::updateCursor(float deltaTime)
{
    //mouse mvt
    unsigned int tileX = static_cast<unsigned int>(_worldPos.x) / _spriteMap._tileSize.x;
    unsigned int tileY = static_cast<unsigned int>(_worldPos.y) / _spriteMap._tileSize.y;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        if (tileX < _spriteMap._mapSize.x && tileY < _spriteMap._mapSize.y) {
            _cursor.setPosition(sf::Vector2f(
                static_cast<float>(tileX * _spriteMap._tileSize.x),
                static_cast<float>(tileY * _spriteMap._tileSize.y)
            ));
        }
    //keyboard mvt
    _moveCooldown -= deltaTime;
    if (_moveCooldown <= 0.f) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            _cursor.setPosition({_cursor.getPosition().x, _cursor.getPosition().y + _tileSize});
            _moveCooldown = _moveInterval;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
            _cursor.setPosition({_cursor.getPosition().x, _cursor.getPosition().y - _tileSize});
            _moveCooldown = _moveInterval;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            _cursor.setPosition({_cursor.getPosition().x - _tileSize, _cursor.getPosition().y});
            _moveCooldown = _moveInterval;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            _cursor.setPosition({_cursor.getPosition().x + _tileSize, _cursor.getPosition().y});
            _moveCooldown = _moveInterval;
        }
    }
    //update current tile
    _currentTile = static_cast<int>(_cursor.getPosition().y / _spriteMap._tileSize.y) * _spriteMap._mapSize.x + 
                   static_cast<int>(_cursor.getPosition().x / _spriteMap._tileSize.x);
}