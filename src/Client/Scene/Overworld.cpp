/*
** Pokemon Primal
** File description:
** Menu
*/

#include <Scene/Overworld.hpp>
#include <Objects/Character.hpp>

Overworld::Overworld()
{
    int value = 0;
}

void Overworld::draw(sf::RenderWindow *window)
{
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

std::shared_ptr<Character> Overworld::getCharacter(std::string tag)
{
    if (_characters.find(tag) != _characters.end())
        return _characters[tag];
    return nullptr;
}

