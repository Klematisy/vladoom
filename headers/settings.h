#pragma once
#include <iostream>
#include <memory>
#include "collisions.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

typedef unsigned int uint;
typedef unsigned char uchar;
typedef std::string String;

struct Entity {
    glm::vec3 position = glm::vec3(1.0f);
    float rotation = 0.0f;
    int hit_points = 100;
};

struct Rect {
    float x;
    float y;
    float x1;
    float y1;
};

struct Point {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    
    float texX;
    float texY;
};

struct Line {
    float k = 1.0f;
    float b = 0.0f;

    void calculate(glm::vec2 p1, glm::vec2 p2);
    float get_x(float y);
    float get_y(float x);
};

struct Vmath {
    static float radians(float angle);
    static float sin(float rotation);
    static float cos(float rotation);
};

class Index_6 {
public:
    int indices[6] = {
        0, 1, 2,
        2, 3, 0,
    };
    Index_6(int koif);
    void convert(uint* arr, int i);
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
    Index_36(int koif);
    void convert(uint* arr, int i);
};

float xR(float x, float y, float rotation);
float zR(float x, float z, float rotation);

void multiply_vec_by_scalar(glm::vec3 &vector, float scalar);

bool inObj(const Map &map, const glm::vec3 &p);

template <typename T>
void remove(std::vector<T>& v, size_t index);

inline std::unique_ptr<int> map;

bool Collides(int stX, int stZ, int x, int z);
int type_of_colls(int stX, int stZ, int x, int z);
bool CollidesRect(int startX, int startZ, float x, float z, float x_half_extent, float z_half_extent);
std::unique_ptr<int> check_collisions(const Entity &creature, const Collisions &colls);