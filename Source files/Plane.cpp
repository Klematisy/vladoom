#include <Plane.h>
#include <vector>
#include <constants.h>

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

void Plane::createShapes(float *plane, uint *indices, uint countOfUnits, float ind) {
    std::vector<Point>   listOfVert;
    std::vector<Index_6> listOfInd;
    uint count = 0;
    float k;

    for (uint i = 0; i < height; i++) {
        for (uint j = i * width; j < (i + 1) * width; j++) {
            if (map[j] == 0) {
                k = j % width - xGap;
                listOfVert.push_back({ (k + 0.0f), yGap, (i + 0.0f), (ind - 1) / COUNT_OF_MATERIALS, 0.0f });
                listOfVert.push_back({ (k + 1.0f), yGap, (i + 0.0f), ind / COUNT_OF_MATERIALS      , 0.0f });
                listOfVert.push_back({ (k + 1.0f), yGap, (i + 1.0f), ind / COUNT_OF_MATERIALS      , 1.0f });
                listOfVert.push_back({ (k + 0.0f), yGap, (i + 1.0f), (ind - 1) / COUNT_OF_MATERIALS, 1.0f });
                listOfInd.push_back(count++);
            }
        }
    }
    int j = 0;
    for (uint i = 0; i < countOfUnits * 20; i+=5) {
        plane[i]     = listOfVert[j].x;
        plane[i + 1] = listOfVert[j].y;
        plane[i + 2] = listOfVert[j].z;
        plane[i + 3] = listOfVert[j].texX;
        plane[i + 4] = listOfVert[j].texY;
        j++;
    }

    j = 0;

    for (uint i = 0; i < countOfUnits * 6; i+=6) {
        listOfInd[j++].convert(indices, i);
    }
}

Plane::Plane(int *map, int width, int height, float xGap, float yGap, float zGpa, float ind)
    : map(map), width(width), height(height), xGap(xGap), yGap(yGap), zGap(zGap)
{
    uint countOfUnits = 0;

    for (int i = 0; i < width * height; i++) {
        if (map[i] == 0) countOfUnits++;
    }

    size = countOfUnits * 6;

    float plane[countOfUnits * 20];
    uint  indices[size];

    createShapes(plane, indices, countOfUnits, ind);

    vao = new VAO();
    vbo = new VBO(plane, sizeof(plane));
    ebo = new EBO(indices, sizeof(indices));

    vao->linkAttrib(*vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*) 0);
    vao->linkAttrib(*vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (3 * sizeof(float)));

    vbo->unbind();
    vao->unbind();
    ebo->unbind();
}

void Plane::draw() {
    vao->bind();
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
}

Plane::~Plane() {
    vao->deleteVao();
    vbo->deleteVbo();
    ebo->deleteEbo();

    delete vao;
    delete vbo;
    delete ebo;
}