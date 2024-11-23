#include <math.h>
#include "libs.h"

void solve(int* map, float* vert, uint* ind, uint countOfUnits, const int mapWidth, const int mapHeight, float width, float xGap, float zGap, float rotation);

Cube::Cube(int *map, int mapWidth, int mapHeight, float width, float xGap, float zGap, float rotation, Collisions& col) {
    uint countOfUnits = 0;

    float xGapfl = std::floor(xGap);
    float zGapfl = std::floor(zGap);

    Map *m = new Map({ map, mapWidth, mapHeight, 
                        -xGapfl + 0.0f,
                        -zGapfl + 0.0f,
                        -(xGapfl + mapWidth + 0.0f),
                        -(zGapfl + mapHeight + 0.0f),
                        xGapfl,
                        zGapfl,
                        width });

    col._piecesOfMap.push_back({m});

    for (int i = 0; i < mapWidth * mapHeight; i++) {
        if (map[i] > 0) countOfUnits++;
    }
    
    size = countOfUnits * 36;

    float vertices[countOfUnits * 40];
    uint  indices[size];

    ind = indices;

    solve(map, vertices, indices, countOfUnits, mapWidth, mapHeight, width, xGap, zGap, rotation);

    vao = new VAO();
    vbo = new VBO(vertices, sizeof(vertices));
    ebo = new EBO(indices,  sizeof(indices));

    vao->linkAttrib(*vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*) 0);
    vao->linkAttrib(*vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (3 * sizeof(float)));

    vbo->unbind();
    vao->unbind();
    ebo->unbind();

    this->xGap = xGap;
    this->zGap = zGap;
}

void Cube::draw() {
    vao->bind();
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
}

void Cube::bind() {
    vao->bind();
}

Cube::~Cube() {
    vao->deleteVao();
    vbo->deleteVbo();
    ebo->deleteEbo();

    delete vao;
    delete vbo;
    delete ebo;
}