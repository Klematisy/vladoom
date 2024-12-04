#include <vector>
#include "libs.h"
#include "VPlane.h"
#include "settings.h"

Vertical_plane::Vertical_plane(float xGap, float zGap, float rotation, float action_pointX, float action_pointZ, int num_of_text, float count_of_objs) {
    std::vector<Point>   listOfVert;
    std::vector<Index_6> listOfInd;

    float stX = action_pointX;
    float stZ = action_pointZ;
 
    listOfVert.push_back({ xR(xGap + 0.0f - stX, zGap - stZ, rotation) + stX, 0.0f, zR(xGap + 0.0f - stX, zGap - stZ, rotation) + stZ,   num_of_text      / count_of_objs,  0.0f});
    listOfVert.push_back({ xR(xGap + 0.0f - stX, zGap - stZ, rotation) + stX, 1.0f, zR(xGap + 0.0f - stX, zGap - stZ, rotation) + stZ,   num_of_text      / count_of_objs,  1.0f});
    listOfVert.push_back({ xR(xGap + 1.0f - stX, zGap - stZ, rotation) + stX, 1.0f, zR(xGap + 1.0f - stX, zGap - stZ, rotation) + stZ,  (num_of_text + 1) / count_of_objs,  1.0f});
    listOfVert.push_back({ xR(xGap + 1.0f - stX, zGap - stZ, rotation) + stX, 0.0f, zR(xGap + 1.0f - stX, zGap - stZ, rotation) + stZ,  (num_of_text + 1) / count_of_objs,  0.0f});

    listOfInd.push_back(0);

    float vertices[20];
    uint   indices[6];
    int j = 0;

    for (int i = 0; i < 20; i+=5) {
        vertices[i]     = listOfVert[j].x;
        vertices[i + 1] = listOfVert[j].y;
        vertices[i + 2] = listOfVert[j].z;
        vertices[i + 3] = listOfVert[j].texX;
        vertices[i + 4] = listOfVert[j].texY;
        j++;
    }

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

void Vertical_plane::deletePlane() {
    vao->deleteVao();
    vbo->deleteVbo();
    ebo->deleteEbo();

    delete vao;
    delete vbo;
    delete ebo;
}