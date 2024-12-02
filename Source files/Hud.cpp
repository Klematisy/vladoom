#include "hud.h"

Hud::Hud() {

    float vertices[16] = {
        -1.0f, -1.0f, 0.0f, 0.0f,
        -1.0f, -0.6f, 0.0f, 1.0f,
         1.0f, -0.6f, 1.0f, 1.0f,
         1.0f, -1.0f, 1.0f, 0.0f
    };

    uint indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    vao = new VAO();
    vbo = new VBO(vertices, sizeof(vertices), GL_STATIC_DRAW);
    ebo = new EBO(indices,  sizeof(indices));

    vao->linkAttrib(*vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*) 0);
    vao->linkAttrib(*vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*) (2 * sizeof(float)));

    vao->unbind();
}

void Hud::draw() {
    vao->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Hud::~Hud() {
    vao->deleteVao();
    vbo->deleteVbo();
    ebo->deleteEbo();

    delete vao;
    delete vbo;
    delete ebo;
}