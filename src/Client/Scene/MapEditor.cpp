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

    _spriteMap.load("assets/tilesmap.png", {16, 16}, createBitMap(12288, 192));
    //_HUD->setGrid(_spriteMap);
}

MapEditor::~MapEditor()
{

}

void MapEditor::draw(sf::RenderWindow *window)
{
    window->setView(_cameraView);

    window->draw(_spriteMap);
    _HUD->draw(*window);
}

void MapEditor::update(float deltaTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        _cameraView.move({0, -_cameraSpeed * deltaTime});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        _cameraView.move({0, _cameraSpeed * deltaTime});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        _cameraView.move({-_cameraSpeed * deltaTime, 0});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        _cameraView.move({_cameraSpeed * deltaTime, 0});
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