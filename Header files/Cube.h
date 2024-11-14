#pragma once

#include <VAO.h>
#include <VBO.h>
#include <EBO.h>
#include <collisions.h>

class Cube {
    uint* ind;
    int size;
    float xGap;
    float zGap;

    VAO* vao;
    VBO* vbo;
    EBO* ebo;
public:
    Cube(int *map, int location, int mapWidth, int mapHeight, float width, float xGap, float zGap, Collisions& col);
    void bind();
    void draw();
    void add();
    Cube() {};
    ~Cube();
};