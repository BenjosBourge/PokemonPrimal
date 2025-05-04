
#include <Objects/Map.hpp>
#include <iostream>

Map::Map()
{

}

void Map::setTriangle(sf::Vertex* tri, int i, sf::Vector2f pos, sf::Vector2f tex) 
{
    tri[i].position = pos;
    tri[i].texCoords = tex;
}

bool Map::load(const std::string& tilesetPath, sf::Vector2u tileSize, const std::vector<std::vector<int>>& tiles)
{
    
    if (!_tileset.loadFromFile(tilesetPath)) {
        std::cerr << "Failed to load tileset!" << std::endl;
        return false;
    }
    
    unsigned int width = tiles[0].size();
    unsigned int height = tiles.size();

    _mapSize = {width, height};
    _tileSize = tileSize;

    _vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    _vertices.resize(width * height * 6); // 6 vertices per tile (2 triangles)

    unsigned int tu_count = _tileset.getSize().x / tileSize.x;
    std::cout << "Tiles count { " << _tileset.getSize().x << ", " << _tileset.getSize().y << " }" << std::endl;

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            int tileNumber = tiles[y][x];

            int tu = tileNumber % tu_count;
            int tv = tileNumber / tu_count;

            sf::Vertex* tri = &_vertices[(x + y * width) * 6];

            sf::Vector2f posTopLeft(x * tileSize.x, y * tileSize.y);
            sf::Vector2f posTopRight((x + 1) * tileSize.x, y * tileSize.y);

            sf::Vector2f posBottomRight((x + 1) * tileSize.x, (y + 1) * tileSize.y);
            sf::Vector2f posBottomLeft(x * tileSize.x, (y + 1) * tileSize.y);

            sf::Vector2f texTopLeft(tu * tileSize.x, tv * tileSize.y);
            sf::Vector2f texTopRight((tu + 1) * tileSize.x, tv * tileSize.y);

            sf::Vector2f texBottomRight((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            sf::Vector2f texBottomLeft(tu * tileSize.x, (tv + 1) * tileSize.y);

            setTriangle(tri, 0, posTopLeft, texTopLeft);
            setTriangle(tri, 1, posTopRight, texTopRight);
            setTriangle(tri, 2, posBottomRight, texBottomRight);
            setTriangle(tri, 3, posTopLeft, texTopLeft);
            setTriangle(tri, 4, posBottomRight, texBottomRight);
            setTriangle(tri, 5, posBottomLeft, texBottomLeft);
        }
    }
    return true;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Apply transform (if needed, ex: scrolling camera)
    states.transform *= getTransform();

    // Apply tileset texture
    states.texture = &_tileset;

    // Draw the vertex array
    target.draw(_vertices, states);
}
