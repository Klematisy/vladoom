#pragma once

#include <GL/glew.h>
#include <VBO.h>

typedef unsigned int uint;

class VAO {
    uint buffer;
public:
    VAO();
    void linkAttrib(VBO& VBO, uint layout, uint numComponents, uint type, GLsizeiptr stride, void* offset);
    void bind();
    void unbind();
    void deleteVao();
};