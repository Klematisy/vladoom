#pragma once

#include "settings.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Vertical_plane {
    int *map;
    uint size;

    VBO* vbo;
    VAO* vao;
    EBO* ebo;

public:
    Vertical_plane(float xGap, float zGap, float rotation, float action_pointX, float action_pointZ);
    Vertical_plane() {}
    void draw();
    void deletePlane();
};

// #include "VPlane.cpp"