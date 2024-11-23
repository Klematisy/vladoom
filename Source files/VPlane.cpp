#include <vector>
#include "libs.h"
#include "VPlane.h"

class Index_6 {
public:
    int indices[6] = {
        0, 1, 2,
        2, 3, 0,
    };
    Index_6(int koif) {
        for (int i = 0; i < 6; i++) {
            indices[i] += koif * 4;
        }
    }
    void convert(uint* arr, int i) {
        for (int j = 0; j < 6; j++) {
            *(arr + i + j) = indices[j];
        }
    }
};

static float sin(float rotation) {
    if      (rotation == 0  ) { return  0.0f; }
    else if (rotation == 90 ) { return  1.0f; }
    else if (rotation == 180) { return  0.0f; }
    else if (rotation == 270) { return -1.0f; }
    else if (rotation == 360) { return  0.0f; }
    else { return glm::sin(glm::radians(rotation)); }
}

static float cos(float rotation) {
    if      (rotation == 0  ) { return  1.0f; }
    else if (rotation == 90 ) { return  0.0f; }
    else if (rotation == 180) { return -1.0f; }
    else if (rotation == 270) { return  0.0f; }
    else if (rotation == 360) { return  1.0f; }
    else { return glm::cos(glm::radians(rotation)); }
}

static float xR(float x, float y, float rotation) {
    glm::mat2 matrix(cos(rotation), -sin(rotation), sin(rotation), cos(rotation));
    x = matrix[0][0] *  x + matrix[0][1] * y;

    return x;
}

static float zR(float x, float y, float rotation) {
    glm::mat2 matrix(cos(rotation), -sin(rotation), sin(rotation), cos(rotation));
    y = matrix[1][0] * x + matrix[1][1] * y;
    
    return y;
}

Vertical_plane::Vertical_plane(float xGap, float zGap, float rotation) {
    std::vector<Point>   listOfVert;
    std::vector<Index_6> listOfInd;

    float stX = xGap + 0.5f;
    float stZ = zGap + 0.5f - 0.001f;
 
    listOfVert.push_back({ xR(xGap + 0.0f - stX, zGap - stZ, rotation) + stX, 0.0f, zR(xGap + 0.0f - stX, zGap - stZ, rotation) + stZ,  9 / 10.0f,  0.0f});
    listOfVert.push_back({ xR(xGap + 0.0f - stX, zGap - stZ, rotation) + stX, 1.0f, zR(xGap + 0.0f - stX, zGap - stZ, rotation) + stZ,  9 / 10.0f,  1.0f});
    listOfVert.push_back({ xR(xGap + 1.0f - stX, zGap - stZ, rotation) + stX, 1.0f, zR(xGap + 1.0f - stX, zGap - stZ, rotation) + stZ, 10 / 10.0f,  1.0f});
    listOfVert.push_back({ xR(xGap + 1.0f - stX, zGap - stZ, rotation) + stX, 0.0f, zR(xGap + 1.0f - stX, zGap - stZ, rotation) + stZ, 10 / 10.0f,  0.0f});

    zGap = stZ + 0.5f - 0.001f;

    listOfVert.push_back({ xR(xGap + 0.0f - stX, zGap - stZ, rotation) + stX, 0.0f, zR(xGap + 0.0f - stX, zGap - stZ, rotation) + stZ,  9 / 10.0f,  0.0f});
    listOfVert.push_back({ xR(xGap + 0.0f - stX, zGap - stZ, rotation) + stX, 1.0f, zR(xGap + 0.0f - stX, zGap - stZ, rotation) + stZ,  9 / 10.0f,  1.0f});
    listOfVert.push_back({ xR(xGap + 1.0f - stX, zGap - stZ, rotation) + stX, 1.0f, zR(xGap + 1.0f - stX, zGap - stZ, rotation) + stZ, 10 / 10.0f,  1.0f});
    listOfVert.push_back({ xR(xGap + 1.0f - stX, zGap - stZ, rotation) + stX, 0.0f, zR(xGap + 1.0f - stX, zGap - stZ, rotation) + stZ, 10 / 10.0f,  0.0f});

    listOfInd.push_back(0);
    listOfInd.push_back(1);

    float vertices[40];
    uint   indices[12];
    int j = 0;

    for (int i = 0; i < 40; i+=5) {
        vertices[i]     = listOfVert[j].x;
        vertices[i + 1] = listOfVert[j].y;
        vertices[i + 2] = listOfVert[j].z;
        vertices[i + 3] = listOfVert[j].texX;
        vertices[i + 4] = listOfVert[j].texY;
        j++;
    }

    listOfInd[0].convert(indices, 0);
    listOfInd[1].convert(indices, 6);

    vao = new VAO();
    vbo = new VBO(vertices, sizeof(vertices));
    ebo = new EBO(indices,  sizeof(indices));

    vao->linkAttrib(*vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*) 0);
    vao->linkAttrib(*vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (3 * sizeof(float)));

    vbo->unbind();
    vao->unbind();
    ebo->unbind();
}

void Vertical_plane::draw() {
    vao->bind();
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
}

void Vertical_plane::deletePlane() {
    vao->deleteVao();
    vbo->deleteVbo();
    ebo->deleteEbo();

    delete vao;
    delete vbo;
    delete ebo;
}