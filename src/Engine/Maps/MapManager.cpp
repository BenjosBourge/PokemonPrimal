/*
** Pokemon Primal
** File description:
** get Map
*/

#include <Maps/MapManager.hpp>
#include <iostream>

MapManager::MapManager()
{
    loadMap(MAP_DEMO_1);
    loadMap(MAP_DEMO_2);
    loadMap(MAP_DEMO_3);
}

void MapManager::loadMap(MapId id)
{
    if (_maps.find(id) == _maps.end()) {
        BitMap map;
        map.getMapFromEnum(id);
        std::cout << "map x: " << map._map[0].size() << " y: " << map._map.size() << std::endl;
        _maps[id] = map;
    }
}