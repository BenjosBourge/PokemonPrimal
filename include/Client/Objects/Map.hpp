#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Map : public sf::Drawable, public sf::Transformable {
    public:
        Map();
        bool load(const std::string &tilesetPath, sf::Vector2u tileSize, const std::vector<std::vector<int>> &tiles);
        bool reload(const std::vector<std::vector<int>> &tiles);
        sf::Vector2u _tileSize;
        sf::Vector2u _mapSize;
        
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void setTriangle(sf::Vertex* tri, int i, sf::Vector2f pos, sf::Vector2f tex);

        sf::VertexArray _vertices;
        sf::Texture _tileset;
};
