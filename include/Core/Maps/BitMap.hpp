/*
** Pokemon Primal
** File description:
** Engine
*/

#pragma once
#include <Maps/Map_Demo.hpp>

enum MapId {
    MAP_DEMO_1,
    MAP_DEMO_2,
    MAP_DEMO_3
};

class Position;

class Tile {
public:
    Tile() {
        _x = 0;
        _y = 0;
        _obstacle = false;
    }

    Tile(int x, int y, bool obstacle) {
        _x = x;
        _y = y;
        _obstacle = obstacle;
    }

    ~Tile() = default;

    int _x;
    int _y;
    bool _obstacle;
    void (*_effect)(Position &position) = nullptr;
};

class BitMap {
public:
    BitMap() = default;
    ~BitMap() = default;

    void setSize(int x, int y);
    void setTile(int x, int y, Tile tile);

    void getMapFromStrings(std::vector<std::string> map);
    void getMapFromEnum(MapId id);

    std::vector<std::vector<Tile>> _map;

};