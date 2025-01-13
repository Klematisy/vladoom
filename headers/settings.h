#pragma once
// std::vector<std::vector<Point>> piecesOfMap;
#include <iostream>
#include <memory>
#include "collisions.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

typedef unsigned int uint;
typedef unsigned char uchar;
typedef std::string String;

struct Rect {
    float x;
    float y;
    float x1;
    float y1;
};

struct Point {
    float x;
    float y;
    float z;

    float texX;
    float texY;
};

struct Vmath {
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
    glm::mat2 matrix(Vmath::cos(rotation), -Vmath::sin(rotation), Vmath::sin(rotation), Vmath::cos(rotation));
    x = matrix[0][0] *  x + matrix[0][1] * y;
    return x;
}

static float zR(float x, float z, float rotation) {
    glm::mat2 matrix(Vmath::cos(rotation), -Vmath::sin(rotation), Vmath::sin(rotation), Vmath::cos(rotation));
    z = matrix[1][0] * x + matrix[1][1] * z;
    return z;
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

static bool inObj(const Map &pathOfMap, const glm::vec3 &p) {
    return (pathOfMap.maxX > p.x && p.x > pathOfMap.minX && pathOfMap.maxZ > p.z && p.z > pathOfMap.minZ);
}

template <typename T>
static void remove(std::vector<T>& v, size_t index) {
    v.erase(v.begin() + index);
}

static std::unique_ptr<int> map;

static bool Collides(int stX, int stZ, int x, int z) {
    return map.get()[12 + (stX - x) + (stZ - z) * 5] == 1;
}

static bool CollidesRect(int startX, int startZ, float x, float z, float x_half_extent, float z_half_extent) {
    return Collides(std::ceil(startX), std::ceil(startZ), std::ceil(x - x_half_extent), std::ceil(z - z_half_extent))
        || Collides(std::ceil(startX), std::ceil(startZ), std::ceil(x + x_half_extent), std::ceil(z - z_half_extent))
        || Collides(std::ceil(startX), std::ceil(startZ), std::ceil(x + x_half_extent), std::ceil(z + z_half_extent))
        || Collides(std::ceil(startX), std::ceil(startZ), std::ceil(x - x_half_extent), std::ceil(z + z_half_extent));
}

struct Entity {
    glm::vec3 position = glm::vec3(1.0f);
    float rotation = 0.0f;
    int hit_points = 100;
};

static std::unique_ptr<int> check_collisions(const Entity &creature, const Collisions &colls) {
    int x, z, x1, z1;
    glm::vec3 point_pos = creature.position;
    
    int *arr = new int[25] {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 2, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0
    };

    for (const Map *pathOfMap : colls._piecesOfMap) {
        for (float rot = 0.0f; rot < 360.0f; rot+=45.0f) {
            point_pos = creature.position;

            x = std::ceil(point_pos.x + pathOfMap->gapX);
            z = std::ceil(point_pos.z + pathOfMap->gapZ);

            point_pos.x += cos(rot);
            point_pos.z += sin(rot);

            x1 = std::ceil(point_pos.x + pathOfMap->gapX);
            z1 = std::ceil(point_pos.z + pathOfMap->gapZ);

            if (inObj(*pathOfMap, point_pos) && pathOfMap->obj[abs(x1) + abs(z1) * pathOfMap->width] > 0) {
                arr[12 + (x - x1) + (z - z1) * 5] = 1;
            }
        }
    }
     
    return (std::unique_ptr<int>) arr;
}
