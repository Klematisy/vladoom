#pragma once
#include <vector>

enum TYPE_OF_COLLISION { 
    UNSHOOTABLE,
    SHOOTABLE
};

struct Map {
    int *obj;
    int width;
    int height;

    float maxX;
    float maxZ;
    float minX;
    float minZ;

    float gap_x, gap_z;

    float size;
    
    TYPE_OF_COLLISION type = SHOOTABLE;
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
