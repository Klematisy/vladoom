#include "VBO.h"

VBO::VBO(float obj[], int size, GLenum type) {
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    if (type == GL_STATIC_DRAW) 
        glBufferData(GL_ARRAY_BUFFER, size, obj, type);
    else
        glBufferData(GL_ARRAY_BUFFER, 0, nullptr, type);
}

void VBO::update(float *obj, int size) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size, obj, GL_DYNAMIC_DRAW);
}

void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::deleteVbo() {
    glDeleteBuffers(1, &buffer);
}