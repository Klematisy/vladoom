#pragma once

#include "libs.h"

class Vertical_plane {
    int *map;
    uint size;

    VBO* vbo;
    VAO* vao;
    EBO* ebo;

public:
    Vertical_plane(float xGap, float zGap, float rotation, float action_pointX, float action_pointZ, int num_of_text, float count_of_objs);
    Vertical_plane() {}
    void draw();
    void deletePlane();
};

// #include "VPlane.cpp"