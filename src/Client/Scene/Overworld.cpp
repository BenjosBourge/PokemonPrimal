/*
** Pokemon Primal
** File description:
** Overworld
*/

#include <Scene/Overworld.hpp>
#include <Objects/Character.hpp>

Overworld::Overworld()
{
    int value = 0;

    /*const int totalElements = 12288;
    const int elementsPerRow = 192;
    const int numRows = std::ceil(totalElements / static_cast<float>(elementsPerRow));
    int value = 0;

    std::vector<std::vector<int>> _bitMap(numRows);

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < elementsPerRow && value < totalElements; ++col) {
            _bitMap[row].push_back(value++);
        }
    }
    _spriteMap.load("assets/tilesmap.png", {16, 16}, _bitMap);*/
}

void Overworld::draw(sf::RenderWindow *window)
{
    //window->draw(_spriteMap);
    for (auto &character : _characters)
        character.second->draw(window, _cameraX, _cameraY);
}

void Overworld::update(float deltaTime)
{
    for (auto &character : _characters)
        character.second->update(deltaTime);
}

void Overworld::addCharacter(std::string tag)
{
    if (_characters.find(tag) == _characters.end()) {
        std::shared_ptr<Character> character = std::make_shared<Character>(CharacterTexture::PLAYER);
        _characters[tag] = character;

        std::cout << "Character " << tag << " added to the overworld." << std::endl;
    }
}

void Overworld::removeCharacter(std::string tag)
{
    if (_characters.find(tag) != _characters.end()) {
        _characters.erase(tag);
        std::cout << "Character " << tag << " removed from the overworld." << std::endl;
    }
}

std::shared_ptr<Character> Overworld::getCharacter(std::string tag)
{
    if (_characters.find(tag) != _characters.end())
        return _characters[tag];
    return nullptr;
}

