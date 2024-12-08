#pragma once
// std::vector<std::vector<Point>> piecesOfMap;
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef unsigned int uint;
typedef unsigned char uchar;
typedef std::string String;

struct Rect {
    float x, y, x1, y1;
};

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

    float size;
};

struct Vla {
    static float radians(float angle) { return angle * 3.14f / 180.0f; }

    static float sin(float rotation) {
        if      (rotation == 0  ) { return  0.0f; }
        else if (rotation == 90 ) { return  1.0f; }
        else if (rotation == 180) { return  0.0f; }
        else if (rotation == 270) { return -1.0f; }
        else if (rotation == 360) { return  0.0f; }
        else { return std::sin(radians(rotation)); }
    }

    static float cos(float rotation) {
        if      (rotation == 0  ) { return  1.0f; }
        else if (rotation == 90 ) { return  0.0f; }
        else if (rotation == 180) { return -1.0f; }
        else if (rotation == 270) { return  0.0f; }
        else if (rotation == 360) { return  1.0f; }
        else { return std::cos(radians(rotation)); }
    }  
};

static float xR(float x, float y, float rotation) {
    glm::mat2 matrix(Vla::cos(rotation), -Vla::sin(rotation), Vla::sin(rotation), Vla::cos(rotation));
    x = matrix[0][0] *  x + matrix[0][1] * y;

    return x;
}

static float zR(float x, float y, float rotation) {
    glm::mat2 matrix(Vla::cos(rotation), -Vla::sin(rotation), Vla::sin(rotation), Vla::cos(rotation));
    y = matrix[1][0] * x + matrix[1][1] * y;
    
    return y;
}

class Index_6 {
public:
    int indices[6] = {
        0, 1, 2,
        2, 3, 0,
    };
    Index_6(int koif) {
        for (int i = 0; i < 6; i++) {
            indices[i] += koif * 4;
        }
    }
    void convert(uint* arr, int i) {
        for (int j = 0; j < 6; j++) {
            *(arr + i + j) = indices[j];
        }
    }
};

struct Index_36 {
    int indices[36] = {
        0, 1, 2,
        2, 3, 0,
        0, 1, 5,
        5, 4, 0,
        1, 5, 6,
        6, 2, 1,
        2, 6, 7,
        7, 3, 2,
        3, 0, 4,
        4, 7, 3,
        4, 5, 6,
        6, 7, 4
    };
    Index_36(int koif) {
        for (int i = 0; i < 36; i++) {
            indices[i] += koif * 8;
        }
    }
    void convert(uint* arr, int i) {
        for (int j = 0; j < sizeof(indices) / sizeof(int); j++) {
            *(arr + i + j) = indices[j];
        }
    }
};

static int toUp(int a) {
    if (a < 0) { a *= (-1); }
    return a;
}

static bool inObj(const Map &pathOfMap, const glm::vec3 &p) {
    return (pathOfMap.maxX > p.x && p.x > pathOfMap.minX && pathOfMap.maxZ > p.z && p.z > pathOfMap.minZ);
}
