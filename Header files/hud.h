#pragma once

#include "libs.h"

class Hud {
    VAO* vao;
    VBO* vbo;
    EBO* ebo;
public:
    Hud(); 
    void draw();
    ~Hud();
};