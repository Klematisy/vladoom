#include "symbol.h"
#include "settings.h"

Symbol::Symbol(float xGap, float yGap, float symbol) : xGap(xGap), yGap(yGap) {
    indices = new uint[6] {
        0, 1, 2,
        2, 3, 0
    };

    vertices = new float[16] {
        -1.0f  + xGap, -1.0f  + yGap,  symbol / 10.0f,      0,
        -1.0f  + xGap, -0.85f + yGap,  symbol / 10.0f,      1,
        -0.95f + xGap, -0.85f + yGap, (symbol + 1) / 10.0f, 1,
        -0.95f + xGap, -1.0f  + yGap, (symbol + 1) / 10.0f, 0
    };

    vao = new VAO();
    vbo = new VBO(nullptr, 0, GL_DYNAMIC_DRAW);
    ebo = new EBO(indices,  24);
}

void Symbol::draw(int symbol) {
    vertices[2]  =  symbol      / 10.0f;
    vertices[6]  =  symbol      / 10.0f;
    vertices[10] = (symbol + 1) / 10.0f;
    vertices[14] = (symbol + 1) / 10.0f;
    vbo->update(64, vertices);
    vao->bind();
    vao->linkAttrib(*vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*) 0);
    vao->linkAttrib(*vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*) (2 * sizeof(float)));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Symbol::~Symbol() {
    vao->deleteVao();
    vbo->deleteVbo();
    ebo->deleteEbo();

    delete vbo;
    delete vao;
    delete ebo;

    delete[] indices;
    delete[] vertices;
}