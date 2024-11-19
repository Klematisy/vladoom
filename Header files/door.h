#pragma once

#include "libs.h"

class Door {
    glm::vec3 pos;
    Cube *cube;
    ProgramShader *ps;
    Map *cols;
public:
    float* coordinate;
    Door(int *map, const  float &xGap, const float &zGap, float rotation, Collisions& col, Texture &tex);
    void clear();
    void draw(glm::vec3 &position, glm::mat4 &view, glm::mat4 &proj, GLFWwindow* window, float rotation);
};