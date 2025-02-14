#pragma once

#include "settings.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Horizontal_plane {
    int *map;
    int width = 0;
    int height = 0;
    float xGap = 0.0f;
    float yGap = 0.0f;
    float zGap = 0.0f;

    uint size;

    VBO *vbo;
    VAO *vao;
    EBO *ebo;

public:
    Horizontal_plane(int *map, int width, int height, float xGap, float yGap, float zGap, int ind, float x_count_of_objs, float y_count_of_objs);
    void draw();
    void clear();
private:
    void createShapes(float *plane, uint *indices, uint countOfUnits, int ind, float x_count_of_objs, float y_count_of_objs);
};