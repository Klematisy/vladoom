#include <math.h>
#include "libs.h"

void Cube::push(std::vector<Point> &listOfVertices, int i, int j, int map_width, float xGap, float zGap, float yCords, float yGap, float width, float rotation, float texInd) {
    float x = (j % map_width) + xGap;
    float z = i + zGap;

    float stX = x + width / 2;
    float stZ = z + CUBE_SIZE / 2;

    listOfVertices.push_back({ xR(x - stX, z - stZ, rotation) + stX, 
                            yCords,
                            zR(x - stX, z - stZ, rotation) + stZ,
                            (texInd - 1) / x_count_of_objs, 
                            yGap });


    listOfVertices.push_back({ xR(x - stX, CUBE_SIZE + z - stZ, rotation) + stX, 
                            yCords,
                            zR(x - stX, CUBE_SIZE + z - stZ, rotation) + stZ, 
                            texInd / x_count_of_objs, 
                            yGap });

    listOfVertices.push_back({ xR(x + width - stX, CUBE_SIZE + z - stZ, rotation) + stX, 
                            yCords,
                            zR(x + width - stX, CUBE_SIZE + z - stZ, rotation) + stZ,
                            (texInd - 1) / x_count_of_objs,
                            yGap });

    listOfVertices.push_back({ xR(x + width - stX, z - stZ, rotation) + stX, 
                            yCords,
                            zR(x + width - stX, z - stZ, rotation) + stZ, 
                            texInd / x_count_of_objs,
                            yGap });
}

void Cube::createShapes(int *map, float *vert, uint *ind, uint countOfUnits, const int map_width, const int map_height, float width, float xGap, float zGap, float rotation) {
    std::vector<Point>    listOfVertices;
    std::vector<Index_36> listOfIndices;

    uint count = 0;
    int xcoo = x_count_of_objs;

    for (int i = 0; i < map_height; i++) {
        for (int j = i * map_width; j < (i + 1) * map_width; j++) {
            if (map[j] > 0) {
                push(listOfVertices, i, j, map_width, xGap, zGap, 0.0f, 1.0f - ((((map[j] - 1) / xcoo) + 1.0f) / y_count_of_objs), width, rotation, (float) (map[j] % xcoo == 0) ? xcoo : map[j] % xcoo);
                push(listOfVertices, i, j, map_width, xGap, zGap, 1.0f, 1.0f - ((((map[j] - 1) / xcoo) + 0.0f) / y_count_of_objs), width, rotation, (float) (map[j] % xcoo == 0) ? xcoo : map[j] % xcoo);
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

Cube::Cube(int *map, int map_width, int map_height, float width, float xGap, float zGap, float rotation, Collisions &col, float x_count_of_objs, float y_count_of_objs) {
    this->x_count_of_objs = x_count_of_objs;
    this->y_count_of_objs = y_count_of_objs;
    
    xGap *= -1;
    zGap *= -1;
    
    uint countOfUnits = 0;

    float xGapfl = std::floor(xGap);
    float zGapfl = std::floor(zGap);

    Map *m = new Map({ map, map_width, map_height, 
                        -xGapfl + 0.0f,
                        -zGapfl + 0.0f,
                        -(xGapfl + map_width + 0.0f),
                        -(zGapfl + map_height + 0.0f),
                        xGapfl,
                        zGapfl,
                        width });

    col._piecesOfMap.push_back({m});

    for (int i = 0; i < map_width * map_height; i++) {
        if (map[i] > 0) countOfUnits++;
    }
    
    size = countOfUnits * 36;

    float *vertices = new float[countOfUnits * 40] {};
    uint  *indices  = new uint[size] {};

    createShapes(map, vertices, indices, countOfUnits, map_width, map_height, width, xGap, zGap, rotation);

    vao = new VAO();
    vbo = new VBO(vertices, 40 * countOfUnits * sizeof(float), GL_STATIC_DRAW);
    ebo = new EBO(indices,  size * sizeof(uint));

    vao->linkAttrib(*vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*) 0);
    vao->linkAttrib(*vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (3 * sizeof(float)));

    vbo->unbind();
    vao->unbind();
    ebo->unbind();

    this->xGap = xGap;
    this->zGap = zGap;

    delete[] vertices;
    delete[] indices;
}

void Cube::draw() {
    vao->bind();
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
}

void Cube::bind() {
    vao->bind();
}

void Cube::clear() {
    vao->deleteVao();
    vbo->deleteVbo();
    ebo->deleteEbo();

    delete vao;
    delete vbo;
    delete ebo;
}