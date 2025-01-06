#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &buffer);
    glBindVertexArray(buffer);
}

void VAO::bind() {
    glBindVertexArray(buffer);
}

void VAO::linkAttrib(VBO& vbo, uint layout, uint size, uint type, GLsizeiptr stride, void* offset) {
    vbo.bind();
    glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vbo.unbind();
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::deleteVao() {
    glDeleteVertexArrays(1, &buffer);
}