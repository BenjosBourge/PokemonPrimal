/*
** Pokemon Primal
** File description:
** get Map
*/

#include <Maps/BitMap.hpp>
#include <Engine/Components/Position.hpp>
#include <iostream>

void BitMap::setSize(int x, int y)
{
    _map.resize(y);
    for (size_t i = 0; i < y; ++i) {
        _map[i].resize(x);
        for (size_t j = 0; j < x; ++j) {
            _map[i][j] = Tile(j, i, false);
        }
    }
}

void BitMap::setTile(int x, int y, Tile tile)
{
    if (y < _map.size() && x < _map[y].size()) {
        _map[y][x] = tile;
    } else {
        std::cerr << "Invalid tile position" << std::endl;
    }
}

void BitMap::getMapFromStrings(std::vector<std::string> map)
{
    std::vector<std::vector<Tile>> new_map;
    for (size_t i = 0; i < map.size(); ++i) {
        std::vector<Tile> line;
        for (size_t j = 0; j < map[i].size(); ++j) {
            Tile tile(j, i, false);

            if (map[i][j] == 'x') {
                tile._obstacle = true;
            }
            if (map[i][j] == '0') {
                tile._effect = [](Position &position) {position.map = MAP_DEMO_1;};
            }
            if (map[i][j] == '1') {
                tile._effect = [](Position &position) {position.map = MAP_DEMO_2;};
            }
            if (map[i][j] == '2') {
                tile._effect = [](Position &position) {position.map = MAP_DEMO_3;};
            }
            line.push_back(tile);
        }
        _map.push_back(line);
    }
}

void BitMap::getMapFromEnum(MapId id)
{
    switch (id) {
        case MAP_DEMO_1:
            getMapFromStrings(mapDemo1);
            break;
        case MAP_DEMO_2:
            getMapFromStrings(mapDemo2);
            break;
        case MAP_DEMO_3:
            getMapFromStrings(mapDemo3);
            break;
        default:
            std::cerr << "Invalid map ID" << std::endl;
            break;
    }
}


