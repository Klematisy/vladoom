#include <math.h>
#include "libs.h"

static void push(std::vector<Point> &listOfVertices, int i, int j, int mapWidth, float xGap, float zGap, float yGap, float width, float rotation, float texInd) {
    float x = (j % mapWidth) + xGap;
    float z = i + zGap;

    float stX = x + width / 2;
    float stZ = z + CUBE_SIZE / 2;

    listOfVertices.push_back({ xR(x - stX, z - stZ, rotation) + stX, 
                            yGap, 
                            zR(x - stX, z - stZ, rotation) + stZ,
                            (texInd - 1) / COUNT_OF_MATERIALS, 
                            yGap });


    listOfVertices.push_back({ xR(x - stX, CUBE_SIZE + z - stZ, rotation) + stX, 
                            yGap,
                            zR(x - stX, CUBE_SIZE + z - stZ, rotation) + stZ, 
                            texInd / COUNT_OF_MATERIALS, 
                            yGap });

    listOfVertices.push_back({ xR(x + width - stX, CUBE_SIZE + z - stZ, rotation) + stX, 
                            yGap,
                            zR(x + width - stX, CUBE_SIZE + z - stZ, rotation) + stZ,
                            (texInd - 1) / COUNT_OF_MATERIALS,
                            yGap });

    listOfVertices.push_back({ xR(x + width - stX, z - stZ, rotation) + stX, 
                            yGap,
                            zR(x + width - stX, z - stZ, rotation) + stZ, 
                            texInd / COUNT_OF_MATERIALS,
                            yGap });
}

void Cube::createShapes(int* map, float* vert, uint* ind, uint countOfUnits, const int mapWidth, const int mapHeight, float width, float xGap, float zGap, float rotation) {
    std::vector<Point>    listOfVertices;
    std::vector<Index_36> listOfIndices;

    uint count = 0;

    for (int i = 0; i < mapHeight; i++) {
        for (int j = i * mapWidth; j < (i + 1) * mapWidth; j++) {
            if (map[j] > 0) {
                push(listOfVertices, i, j, mapWidth, xGap, zGap, 0.0f, width, rotation, map[j] + 0.0f);
                push(listOfVertices, i, j, mapWidth, xGap, zGap, 1.0f, width, rotation, map[j] + 0.0f);
                listOfIndices.push_back(count++);
            }
        }
    }

    int j = 0;

    for (int i = 0; i < countOfUnits * 40; i+=5) {
        vert[i]     = listOfVertices[j].x;
        vert[i + 1] = listOfVertices[j].y;
        vert[i + 2] = listOfVertices[j].z;
        vert[i + 3] = listOfVertices[j].texX;
        vert[i + 4] = listOfVertices[j].texY;
        j++;
    }
    j = 0;
    for (int i = 0; i < countOfUnits * 36; i+=36) {
        listOfIndices[j].convert(ind, i);
        j++;
    }
}

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

    createShapes(map, vertices, indices, countOfUnits, mapWidth, mapHeight, width, xGap, zGap, rotation);

    vao = new VAO();
    vbo = new VBO(vertices, sizeof(vertices), GL_STATIC_DRAW);
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