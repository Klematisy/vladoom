#pragma once

#include <GL/glew.h>

typedef unsigned int uint;

class EBO {
    uint buffer;
public:
    EBO(uint indices[], int size) ;
    void bind();
    void unbind();
    void deleteEbo();
};