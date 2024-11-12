#pragma once

#include <GL/glew.h>

typedef unsigned int uint;

class VBO {
    uint buffer;
public:
    VBO(float obj[], int size);
    void bind();
    void unbind();
    void deleteVbo();
};