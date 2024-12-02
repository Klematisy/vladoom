#pragma once

#include "libs.h"

class Symbol {
    float xGap;
    float yGap;

    uint   *indices;
    float *vertices;
    
    VBO* vbo;
    VAO* vao;
    EBO* ebo;
public:
    Symbol(float xGap, float yGap, float symbol);
    void draw(int symbol);
    ~Symbol();
};