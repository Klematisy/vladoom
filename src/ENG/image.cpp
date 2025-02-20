#include "image.h"

Image::Image(GLenum type, float x_gap, float y_gap, float width, float height, float opacity)
    : type(type), x_gap(x_gap), y_gap(y_gap), width(width), height(height)
{   
    float stX = -1.0f;
    float stY = -1.0f;
    float vertices[] = {
        stX         + x_gap,  stY          + y_gap, 0.0f, 0.0f, opacity,
        stX         + x_gap,  stY + height + y_gap, 0.0f, 1.0f, opacity,
        stX + width + x_gap,  stY + height + y_gap, 1.0f, 1.0f, opacity,
        stX + width + x_gap,  stY          + y_gap, 1.0f, 0.0f, opacity
    };

    uint indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    vao = new VAO();
    vbo = new VBO(vertices, 20 * sizeof(float), type);
    ebo = new EBO(indices,  6 * sizeof(uint));

    vao->linkAttrib(*vbo, 0, 2, GL_FLOAT, 5 * sizeof(float), (void*) 0);
    vao->linkAttrib(*vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (2 * sizeof(float)));
    vao->linkAttrib(*vbo, 2, 1, GL_FLOAT, 5 * sizeof(float), (void*) (4 * sizeof(float)));

    vao->unbind();
}

void Image::draw(Rect *r, float opacity) {
    vao->bind();
    if (type == GL_DYNAMIC_DRAW) {
        float stX = -1.0f;
        float stY = -1.0f;

        float vertices[] = {
            stX         + x_gap,  stY          + y_gap, r->x,  r->y,  opacity,
            stX         + x_gap,  stY + height + y_gap, r->x,  r->y1, opacity,
            stX + width + x_gap,  stY + height + y_gap, r->x1, r->y1, opacity,
            stX + width + x_gap,  stY          + y_gap, r->x1, r->y,  opacity
        };

        vbo->update(vertices, sizeof(float) * 20);
        vao->linkAttrib(*vbo, 0, 2, GL_FLOAT, 5 * sizeof(float), (void*) 0);
        vao->linkAttrib(*vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (2 * sizeof(float)));
        vao->linkAttrib(*vbo, 2, 1, GL_FLOAT, 5 * sizeof(float), (void*) (4 * sizeof(float)));
    }
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Image::draw_once(float x_gap, float y_gap, float width, float height, Rect *r, float opacity) {
    float stX = -1.0f;
    float stY = -1.0f;
    float vertices[] = {
        stX         + x_gap,  stY          + y_gap, r->x,  r->y,  opacity,
        stX         + x_gap,  stY + height + y_gap, r->x,  r->y1, opacity,
        stX + width + x_gap,  stY + height + y_gap, r->x1, r->y1, opacity,
        stX + width + x_gap,  stY          + y_gap, r->x1, r->y,  opacity
    };

    uint indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VAO vao;
    VBO vbo(vertices, 20 * sizeof(float), GL_DYNAMIC_DRAW);
    EBO ebo(indices,  6 * sizeof(uint));

    vbo.update(vertices, sizeof(float) * 20);
    vao.linkAttrib(vbo, 0, 2, GL_FLOAT, 5 * sizeof(float), (void*) 0);
    vao.linkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (2 * sizeof(float)));
    vao.linkAttrib(vbo, 2, 1, GL_FLOAT, 5 * sizeof(float), (void*) (4 * sizeof(float)));

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