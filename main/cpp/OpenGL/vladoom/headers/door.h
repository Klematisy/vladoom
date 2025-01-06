#pragma once

#include "VPlane.h"

class Door {
    glm::vec3 pos;
    Cube *cube;
    Vertical_plane *plane;
    Vertical_plane *plane1;
    ProgramShader *psCube;
    ProgramShader *psTex;
    Map *cols;
public:
    float* coordinate;
    Door(int *map, const  float &xGap, const float &zGap, float rotation, Collisions& col, Texture &tex);
    ~Door();
    void clear();
    void draw(glm::vec3 &position, glm::mat4 &view, glm::mat4 &proj, GLFWwindow* window, float rotation);
};