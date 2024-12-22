#include "image.h"

Image::Image(GLenum type, float x_gap, float y_gap, float width, float height)
    : type(type), x_gap(x_gap), y_gap(y_gap), width(width), height(height)
{   
    float stX = -1.0f;
    float stY = -1.0f;
    float vertices[] = {
        stX         + x_gap,  stY          + y_gap, 0.0f, 0.0f,
        stX         + x_gap,  stY + height + y_gap, 0.0f, 1.0f,
        stX + width + x_gap,  stY + height + y_gap, 1.0f, 1.0f,
        stX + width + x_gap,  stY          + y_gap, 1.0f, 0.0f
    };

    uint indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    vao = new VAO();
    vbo = new VBO(vertices, 16 * sizeof(float), type);
    ebo = new EBO(indices,  6 * sizeof(uint));

    vao->linkAttrib(*vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*) 0);
    vao->linkAttrib(*vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*) (2 * sizeof(float)));

    vao->unbind();
}

void Image::draw(Rect *r) {
    vao->bind();
    if (type == GL_DYNAMIC_DRAW) {
        float stX = -1.0f;
        float stY = -1.0f;

        float vertices[] = {
            stX         + x_gap,  stY          + y_gap, r->x,  r->y,
            stX         + x_gap,  stY + height + y_gap, r->x,  r->y1,
            stX + width + x_gap,  stY + height + y_gap, r->x1, r->y1,
            stX + width + x_gap,  stY          + y_gap, r->x1, r->y
        };

        vbo->update(sizeof(float) * 16, vertices);
        vao->linkAttrib(*vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*) 0);
        vao->linkAttrib(*vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*) (2 * sizeof(float)));
    }
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Image::draw_once(float x_gap, float y_gap, float width, float height, Rect *r) {
    float stX = -1.0f;
    float stY = -1.0f;
    float vertices[] = {
        stX         + x_gap,  stY          + y_gap, r->x,  r->y,
        stX         + x_gap,  stY + height + y_gap, r->x,  r->y1,
        stX + width + x_gap,  stY + height + y_gap, r->x1, r->y1,
        stX + width + x_gap,  stY          + y_gap, r->x1, r->y
    };

    uint indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VAO vao;
    VBO vbo(vertices, 16 * sizeof(float), GL_DYNAMIC_DRAW);
    EBO ebo(indices,  6 * sizeof(uint));

    vbo.update(sizeof(float) * 16, vertices);
    vao.linkAttrib(vbo, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*) 0);
    vao.linkAttrib(vbo, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*) (2 * sizeof(float)));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    vao.deleteVao();
    vbo.deleteVbo();
    ebo.deleteEbo();
}

void Image::clear() {
    vao->deleteVao();
    vbo->deleteVbo();
    ebo->deleteEbo();

    delete vao;
    delete vbo;
    delete ebo;
}