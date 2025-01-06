#include <vector>
#include "libs.h"
#include "VPlane.h"
#include "settings.h"

Vertical_plane::Vertical_plane(float xGap, 
                               float zGap, 
                               float rotation, 
                               float action_pointX, 
                               float action_pointZ, 
                               int x_tex,
                               int y_tex,
                               float x_count_of_objs,
                               float y_count_of_objs) 
{
    std::vector<Index_6> listOfInd;

    float stX = action_pointX;
    float stZ = action_pointZ;

    listOfInd.push_back(0);

    uint   indices[6];
    int j = 0;

    float vertices[20] = {
        -xR(xGap - 0.0f - stX, zGap - stZ, rotation) - stX, 0.0f, -zR(xGap - 0.0f - stX, zGap - stZ, rotation) - stZ,   x_tex      / x_count_of_objs,  (y_tex)      / y_count_of_objs,
        -xR(xGap - 0.0f - stX, zGap - stZ, rotation) - stX, 1.0f, -zR(xGap - 0.0f - stX, zGap - stZ, rotation) - stZ,   x_tex      / x_count_of_objs,  (y_tex + 1)  / y_count_of_objs,
        -xR(xGap - 1.0f - stX, zGap - stZ, rotation) - stX, 1.0f, -zR(xGap - 1.0f - stX, zGap - stZ, rotation) - stZ,  (x_tex + 1) / x_count_of_objs,  (y_tex + 1)  / y_count_of_objs,
        -xR(xGap - 1.0f - stX, zGap - stZ, rotation) - stX, 0.0f, -zR(xGap - 1.0f - stX, zGap - stZ, rotation) - stZ,  (x_tex + 1) / x_count_of_objs,  (y_tex)      / y_count_of_objs
    };

    listOfInd[0].convert(indices, 0);

    vao = new VAO();
    vbo = new VBO(vertices, sizeof(vertices), GL_STATIC_DRAW);
    ebo = new EBO(indices,  sizeof(indices));

    vao->linkAttrib(*vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*) 0);
    vao->linkAttrib(*vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (3 * sizeof(float)));

    vbo->unbind();
    vao->unbind();
    ebo->unbind();
}

void Vertical_plane::draw() {
    vao->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Vertical_plane::draw_once(float xGap, 
                               float zGap, 
                               float rotation, 
                               float action_pointX, 
                               float action_pointZ, 
                               int x_tex,
                               int y_tex,
                               float x_count_of_objs,
                               float y_count_of_objs) 
{
    float stX = action_pointX;
    float stZ = action_pointZ;

    float vertices[20] = {
        xR(xGap + 0.0f - stX, zGap - stZ, rotation) + stX, 0.0f, zR(xGap + 0.0f - stX, zGap - stZ, rotation) + stZ,   x_tex      / x_count_of_objs,  (y_tex)      / y_count_of_objs,
        xR(xGap + 0.0f - stX, zGap - stZ, rotation) + stX, 1.0f, zR(xGap + 0.0f - stX, zGap - stZ, rotation) + stZ,   x_tex      / x_count_of_objs,  (y_tex + 1)  / y_count_of_objs,
        xR(xGap + 1.0f - stX, zGap - stZ, rotation) + stX, 1.0f, zR(xGap + 1.0f - stX, zGap - stZ, rotation) + stZ,  (x_tex + 1) / x_count_of_objs,  (y_tex + 1)  / y_count_of_objs,
        xR(xGap + 1.0f - stX, zGap - stZ, rotation) + stX, 0.0f, zR(xGap + 1.0f - stX, zGap - stZ, rotation) + stZ,  (x_tex + 1) / x_count_of_objs,  (y_tex)      / y_count_of_objs
    };

    uint indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    VAO vao;
    VBO vbo(nullptr, 0, GL_DYNAMIC_DRAW);
    vbo.update(vertices, sizeof(vertices));
    EBO ebo(indices,  sizeof(indices));


    vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*) 0);
    vao.linkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    vbo.unbind();
    vao.unbind();
    ebo.unbind();

}

void Vertical_plane::deletePlane() {
    vao->deleteVao();
    vbo->deleteVbo();
    ebo->deleteEbo();

    delete vao;
    delete vbo;
    delete ebo;
}