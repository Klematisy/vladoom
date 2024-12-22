#pragma once

#include <GL/glew.h>

typedef unsigned int uint;

class VBO {
    uint buffer;
    float *obj;
public:
    VBO(float obj[], int size, GLenum type);
    void update(int size, float *obj);
    void bind();
    void unbind();
    void deleteVbo();
};