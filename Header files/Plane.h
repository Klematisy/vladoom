#include <settingsAndVars.h>
#include <VAO.h>
#include <VBO.h>
#include <EBO.h>

class Plane {
    int *map;
    int width;
    int height;
    float xGap;
    float yGap;
    float zGap;

    float xRotation;
    float yRotation;
    float zRotation;

    uint size;

    VBO* vbo;
    VAO* vao;
    EBO* ebo;

public:
    Plane(int *map, int width, int height, float xGap, float yGap, float zGap, float xRotation, float yRotation, float zRotation, float ind);
    void draw();
    ~Plane();
private:
    void createShapes(float *plane, uint* indices, uint countOfUnits, float ind);
};