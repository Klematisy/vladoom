#pragma once

#include <GL/glew.h>

typedef unsigned int uint;

class VBO {
    uint buffer;
    float *obj;
public:
    VBO(float obj[], int size, GLenum type);
    void update(float *obj, int size);
    void bind();
    void unbind();
    void deleteVbo();
};