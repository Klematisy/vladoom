#pragma once

#include "settingsAndVars.h"
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
    Vertical_plane(float xGap, float zGap, float rotation);
    Vertical_plane() {}
    void draw();
    void deletePlane();
};

// #include "VPlane.cpp"