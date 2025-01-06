#pragma once

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "settings.h"

class Image {
    GLenum type;
    
    float x_gap;
    float y_gap;

    float width;
    float height;

    VBO *vbo;
    VAO *vao;
    EBO *ebo;
public:
    Image(GLenum type, float x_gap, float y_gap, float width, float height);
    void draw(Rect *rect);
    static void draw_once(float x_gap, float y_gap, float width, float height, Rect *r);
    void clear();
};