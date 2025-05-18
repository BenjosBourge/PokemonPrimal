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

    _mapList.push_back(_spriteMap);
    _mapList.push_back(_editMap);
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
    window->draw(_mapList[_viewSelector]);
    if(_viewSelector == VIEW_EDIT)
        _HUD->draw(*window);
}


void MapEditor::update(float deltaTime)
{
} 

void MapEditor::handleEvent(const std::optional<sf::Event>& event, float deltaTime) {
    if (!event) return;

    if (const auto* key = event->getIf<sf::Event::KeyPressed>())
        handleKeyPress(key->code, deltaTime);

    if (const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
        _cameraView.zoom(mouseWheelScrolled->delta > 0 ? 0.9f : 1.1f);
    
    //mouse mvt of the cursor
    unsigned int tileX = static_cast<unsigned int>(_worldPos.x) / _mapList[_viewSelector]._tileSize.x;
    unsigned int tileY = static_cast<unsigned int>(_worldPos.y) / _mapList[_viewSelector]._tileSize.y;

    if (const auto* mouseMoved = event->getIf<sf::Event::MouseButtonPressed>())
        if (mouseMoved->button == sf::Mouse::Button::Left) {
            _currentTile = tileY * _mapList[_viewSelector]._mapSize.x + tileX;
            std::cout << "Tile { " << _currentTile << " } is selected" << std::endl;
             _mapList[_viewSelector].highlightTile(_currentTile, _highlightedColor);
        }
}

void MapEditor::handleKeyPress(sf::Keyboard::Key code, float deltaTime) {
    switch (code) {
        case sf::Keyboard::Key::Enter:
            writeTileIfValid();
            break;
        
        // Switch between views
        case sf::Keyboard::Key::Num1:
            _viewSelector = VIEW_SPRITESHEET;
            break;
        case sf::Keyboard::Key::Num2:
            _viewSelector = VIEW_EDIT;
            break;

        case sf::Keyboard::Key::Space:
            resetCamera();
            break;

        // Save the current tile
        case sf::Keyboard::Key::C:
            saveCurrentTile();
            break;
        
        // Camera movement
        case sf::Keyboard::Key::Up:
            _cameraView.move({0, -_cameraSpeed * deltaTime});
            break;
        case sf::Keyboard::Key::Down:
            _cameraView.move({0, _cameraSpeed * deltaTime});
            break;
        case sf::Keyboard::Key::Left:
            _cameraView.move({-_cameraSpeed * deltaTime, 0});
            break;
        case sf::Keyboard::Key::Right:
            _cameraView.move({_cameraSpeed * deltaTime, 0});
            break;
        
        // Zoom in and out
        case sf::Keyboard::Key::O:
            _cameraView.zoom(0.9f);
            break;
        case sf::Keyboard::Key::P:
            _cameraView.zoom(1.1f);
            break;

        // Cursor movement
        case sf::Keyboard::Key::Z:
            _currentTile = _mapList[_viewSelector].highlightTile(_currentTile - _mapList[_viewSelector]._mapSize.x, _highlightedColor);
            break;
        case sf::Keyboard::Key::Q:
             _currentTile = _mapList[_viewSelector].highlightTile(_currentTile - 1, _highlightedColor);
            break;
        case sf::Keyboard::Key::S:
            _currentTile = _mapList[_viewSelector].highlightTile(_currentTile + _mapList[_viewSelector]._mapSize.x, _highlightedColor);
            break;
        case sf::Keyboard::Key::D:
            _currentTile = _mapList[_viewSelector].highlightTile(_currentTile + 1, _highlightedColor);
            break;
        default:
            break;
    }
}

void MapEditor::writeTileIfValid() {
    if (_viewSelector == VIEW_EDIT) {
        std::cout << "Tile { " << _savedTile << " " << _currentTile / _mapList[_viewSelector]._mapSize.x << " " << _currentTile % _mapList[_viewSelector]._mapSize.x << " } is written" << std::endl;
        _emptyBitMap[_currentTile / _mapList[_viewSelector]._mapSize.x][_currentTile % _mapList[_viewSelector]._mapSize.x] = _savedTile;
        _mapList[_viewSelector].reload(_emptyBitMap);
    }
}

void MapEditor::resetCamera() {
    _cameraView.setCenter({960, 540});
    _cameraView.setSize({1920, 1080});
}

void MapEditor::saveCurrentTile() {
    std::cout << "Tile { " << _currentTile << " } is saved" << std::endl;
    _savedTile = _currentTile;
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
    
    for (int row = 0; row < numRows; ++row)
        for (int col = 0; col < elementsPerRow && value < totalElements; ++col)
            _bitMap[row].push_back(value++);
    return _bitMap;
}

void MapEditor::printBitMap(const std::vector<std::vector<int>>& bitMap)
{
    for (const auto& row : bitMap) {
        for (const auto& elem : row)
            std::cout << elem << " ";
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> MapEditor::createEmptyBitMap(int x, int y)
{
    int totalElements = x * y;
    int elementsPerRow = x;

    if (totalElements == 0) {
        std::vector<std::vector<int>> _bitMap(1);
        return _bitMap;
    }
    const int numRows = std::ceil(totalElements / static_cast<float>(elementsPerRow));
    int value = 0;
    
    std::vector<std::vector<int>> _bitMap(numRows);
    
    for (int row = 0; row < numRows; ++row)
        for (int col = 0; col < elementsPerRow && value < totalElements; ++col)
            _bitMap[row].push_back(0);
    return _bitMap;
}
