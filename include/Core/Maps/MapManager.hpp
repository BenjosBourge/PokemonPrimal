/*
** Pokemon Primal
** File description:
** Engine
*/

#pragma once
#include <string>
#include <Maps/BitMap.hpp>
#include <map>

class MapManager {
public:
    MapManager();
    ~MapManager() = default;

    void loadMap(MapId id);

    std::map<MapId, BitMap> _maps;
};
