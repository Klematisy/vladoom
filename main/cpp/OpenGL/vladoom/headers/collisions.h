#pragma once
#include <vector>

struct Map {
    int* obj;
    int width;
    int height;

    float maxX;
    float maxZ;
    float minX;
    float minZ;

    float gapX, gapZ;

    float size;
};

class Door;

class Collisions {
public:
    std::vector<Map*> _piecesOfMap;
    ~Collisions() {
        while (_piecesOfMap.size() > 0) {
            delete _piecesOfMap[_piecesOfMap.size() - 1];
            _piecesOfMap.pop_back();
        }
    }
};
