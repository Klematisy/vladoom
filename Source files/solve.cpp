#include <libs.h>
#include <settingsAndVars.h>

struct Index_36 {
    int indices[36] = {
        0, 1, 2,
        2, 3, 0,
        0, 1, 5,
        5, 4, 0,
        1, 5, 6,
        6, 2, 1,
        2, 6, 7,
        7, 3, 2,
        3, 0, 4,
        4, 7, 3,
        4, 5, 6,
        6, 7, 4
    };
    Index_36(int koif) {
        for (int i = 0; i < 36; i++) {
            indices[i] += koif * 8;
        }
    }
    void convert(uint* arr, int i) {
        for (int j = 0; j < sizeof(indices) / sizeof(int); j++) {
            *(arr + i + j) = indices[j];
        }
    }
};

void push(std::vector<Point> &listOfVertices, int i, int j, int mapWidth, float xGap, float zGap, float yGap, float texInd) {
    float x = (j % mapWidth) + xGap;
    float z = i + zGap;
    listOfVertices.push_back({             x, yGap,             z, 0.0f, 0.0f, texInd });
    listOfVertices.push_back({             x, yGap, CUBE_SIZE + z, 1.0f, 0.0f, texInd });
    listOfVertices.push_back({ CUBE_SIZE + x, yGap, CUBE_SIZE + z, 0.0f, 0.0f, texInd });
    listOfVertices.push_back({ CUBE_SIZE + x, yGap,             z, 1.0f, 0.0f, texInd });
    
    listOfVertices.push_back({             x, 1.0f + yGap,             z, 0.0f, 1.0f, texInd });
    listOfVertices.push_back({             x, 1.0f + yGap, CUBE_SIZE + z, 1.0f, 1.0f, texInd });
    listOfVertices.push_back({ CUBE_SIZE + x, 1.0f + yGap, CUBE_SIZE + z, 0.0f, 1.0f, texInd });
    listOfVertices.push_back({ CUBE_SIZE + x, 1.0f + yGap,             z, 1.0f, 1.0f, texInd });
}

void solve(int* map, float* vert, uint* ind, uint countOfUnits, const int mapWidth, const int mapHeight, float xGap, float zGap, float yGap) {
    std::vector<Point>    listOfVertices;
    std::vector<Index_36> listOfIndices;

    uint count = 0;

    for (int i = 0; i < mapHeight; i++) {
        for (int j = i * mapWidth; j < (i + 1) * mapWidth; j++) {
            if (map[j] > 0) {
                push(listOfVertices, i, j, mapWidth, xGap, zGap, yGap, map[j] + 0.0f);
                listOfIndices.push_back(count++);
            }
        }
    }

    int j = 0;

    for (int i = 0; i < countOfUnits * 48; i+=6) {
        vert[i]     = listOfVertices[j].x;
        vert[i + 1] = listOfVertices[j].y;
        vert[i + 2] = listOfVertices[j].z;
        vert[i + 3] = listOfVertices[j].texX;
        vert[i + 4] = listOfVertices[j].texY;
        vert[i + 5] = listOfVertices[j].texIndex;
        j++;
    }
    j = 0;
    for (int i = 0; i < countOfUnits * 36; i+=36) {
        listOfIndices[j].convert(ind, i);
        j++;
    }
}