#pragma once

#include "settings.h"

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