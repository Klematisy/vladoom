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

void solve(int* map, float* vert, uint* ind, uint countOfUnits, const int mapWidth, const int mapHeight, float width, float xGap, float zGap, float rotation) {
    std::vector<Point>    listOfVertices;
    std::vector<Index_36> listOfIndices;

    std::cout << xR(0, 1, 90.0f) << " " << zR(0, 1, 90.0f) << std::endl;

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