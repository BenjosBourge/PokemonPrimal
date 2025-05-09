#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

#define TILE_SIZE 48

extern sf::Font globalFont;

class TextureManager {
public:
    TextureManager() = default;
    ~TextureManager() = default;

    sf::Texture &getTexture(const std::string &texturePath) {
        if (_textures.find(texturePath) == _textures.end()) {
            sf::Texture texture;
            if (!texture.loadFromFile("assets/" + texturePath + ".png")) {
                std::cerr << "Error loading texture: " << texturePath << std::endl;
            }
            _textures[texturePath] = texture;
        }
        return _textures[texturePath];
    }

    std::map<std::string, sf::Texture> _textures;
};

extern TextureManager globalTextures;

#endif
