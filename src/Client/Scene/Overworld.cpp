/*
** Pokemon Primal
** File description:
** Menu
*/

#include <Scene/Overworld.hpp>

Overworld::Overworld()
{
    _spriteMap.load("assets/tilesmap.png", {16, 16}, _bitMap);
}

void Overworld::draw(Game &game)
{
    game.getWindow()->draw(_spriteMap);
    for (auto &character : _characters) {
        character.second->draw(game);
    }
}

void Overworld::update(float deltaTime)
{

}

void Overworld::addCharacter(std::string tag)
{
    if (_characters.find(tag) == _characters.end()) {
        std::shared_ptr<Character> character = std::make_shared<Player>(CharacterTexture::PLAYER);
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

