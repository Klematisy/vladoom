#pragma once
// std::vector<std::vector<Point>> piecesOfMap;
#include <iostream>

typedef unsigned int uint;
typedef unsigned char uchar;
typedef std::string String;

struct Point {
    float x;
    float y;
    float z;

    float texX;
    float texY;
};

struct Map {
    int* obj;
    int width;
    int height;
    
    float maxX;
    float maxZ;
    float minX;
    float minZ;

    float gapX, gapZ;
};