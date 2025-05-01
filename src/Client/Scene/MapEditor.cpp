/*
** Pokemon Primal
** File description:
** SceneEditor
*/

#include <Scene/MapEditor.hpp>


MapEditor::MapEditor()
{
    const int totalElements = 12288;
    const int elementsPerRow = 192;
    const int numRows = std::ceil(totalElements / static_cast<float>(elementsPerRow));
    int value = 0;

    std::vector<std::vector<int>> _bitMap(numRows);

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < elementsPerRow && value < totalElements; ++col) {
            _bitMap[row].push_back(value++);
        }
    }
    _spriteMap.load("assets/tilesmap.png", {16, 16}, _bitMap);
}

MapEditor::~MapEditor()
{

}

void MapEditor::draw(sf::RenderWindow *window)
{
    window->draw(_spriteMap);
}

void MapEditor::update(float deltaTime)
{

}