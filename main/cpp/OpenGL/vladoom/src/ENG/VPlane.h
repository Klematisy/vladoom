#pragma once

#include "libs.h"

class Vertical_plane {
    int *map;
    uint size;

    VBO* vbo;
    VAO* vao;
    EBO* ebo;

public:
    Vertical_plane(float xGap,
                   float zGap,
                   float rotation,
                   float action_pointX,
                   float action_pointZ,
                   int x_tex,
                   int y_tex,
                   float x_count_of_objs,
                   float y_count_of_objs);
    Vertical_plane() {}
    void draw();
    static void draw_once(float xGap,
                          float zGap,
                          float rotation,
                          float action_pointX,
                          float action_pointZ,
                          int x_tex,
                          int y_tex,
                          float x_count_of_objs,
                          float y_count_of_objs);
    void deletePlane();
};

// #include "VPlane.cpp"