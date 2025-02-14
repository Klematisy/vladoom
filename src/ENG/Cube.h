#pragma once

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "collisions.h"
#include "settings.h"

class Cube {
    int   size;
    float xGap;
    float zGap;

    VAO *vao;
    VBO *vbo;
    EBO *ebo;
    Map *m;
    
    float x_count_of_objs;
    float y_count_of_objs;
    
    void push(std::vector<Point> &listOfVertices, int i, int j, int map_width, float xGap, float zGap, float yCords, float yGap, float width, float rotation, float texInd);
public:
    Cube(int *map, 
         int map_width, int map_height, 
         float width, 
         float xGap, float zGap, float rotation, 
         Collisions &col, 
         float x_count_of_objs, float y_count_of_objs);
    void createShapes(int *map, float *vert, uint *ind, uint countOfUnits, const int map_width, const int map_height, float width, float xGap, float zGap, float rotation);
    void bind();
    void draw();
    void add();
    Cube() {};
    void clear();
};