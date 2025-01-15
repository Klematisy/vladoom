#include <vector>
#include "Plane.h"
#include "constants.h"

void Horizontal_plane::createShapes(float *plane, uint *indices, uint countOfUnits, int ind, float x_count_of_objs, float y_count_of_objs) {
    std::vector<Point>   listOfVert;
    std::vector<Index_6> listOfInd;
    uint count = 0;
    float k;
    
    int xcoo = x_count_of_objs;

    for (uint i = 0; i < height; i++) {
        for (uint j = i * width; j < (i + 1) * width; j++) {
            if (map[j] == 0) {
                int res1 = ( ind      % xcoo == 0) ? xcoo     :  ind      % xcoo;
                int res2 = ((ind - 1) % xcoo == 0) ? xcoo - 1 : (ind - 1) % xcoo;
                
                k = j % width + xGap;
                listOfVert.push_back({ (k + 0.0f), yGap, (i + 0.0f + zGap), ( res2) / x_count_of_objs, 1.0f - ((((ind - 1) / xcoo) + 1.0f) / y_count_of_objs) });
                listOfVert.push_back({ (k + 1.0f), yGap, (i + 0.0f + zGap), ( res1) / x_count_of_objs, 1.0f - ((((ind - 1) / xcoo) + 1.0f) / y_count_of_objs) });
                listOfVert.push_back({ (k + 1.0f), yGap, (i + 1.0f + zGap), ( res1) / x_count_of_objs, 1.0f - ((((ind - 1) / xcoo) + 0.0f) / y_count_of_objs) });
                listOfVert.push_back({ (k + 0.0f), yGap, (i + 1.0f + zGap), ( res2) / x_count_of_objs, 1.0f - ((((ind - 1) / xcoo) + 0.0f) / y_count_of_objs) });
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

Horizontal_plane::Horizontal_plane(int *map, int width, int height, float xGap, float yGap, float zGap, int ind, float x_count_of_objs, float y_count_of_objs)
    : map(map), width(width), height(height), xGap(xGap), yGap(yGap), zGap(zGap)
{
    uint countOfUnits = 0;

    for (int i = 0; i < width * height; i++) {
        if (map[i] == 0) countOfUnits++;
    }

    size = countOfUnits * 6;

    float plane[countOfUnits * 20];
    uint  indices[size];

    createShapes(plane, indices, countOfUnits, ind, x_count_of_objs, y_count_of_objs);

    vao = new VAO();
    vbo = new VBO(plane, sizeof(plane), GL_STATIC_DRAW);
    ebo = new EBO(indices, sizeof(indices));

    vao->linkAttrib(*vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*) 0);
    vao->linkAttrib(*vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (3 * sizeof(float)));

    vbo->unbind();
    vao->unbind();
    ebo->unbind();
}

void Horizontal_plane::draw() {
    vao->bind();
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
}

Horizontal_plane::~Horizontal_plane() {
    vao->deleteVao();
    vbo->deleteVbo();
    ebo->deleteEbo();

    delete vao;
    delete vbo;
    delete ebo;
}